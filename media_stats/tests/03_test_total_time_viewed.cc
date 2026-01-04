#include <cstdio>

#include "basic_testing.h"

#include "../media_stats.h"

TEST(nonexistent_media) {
    CHECK_ALMOST_EQUAL(total_time_viewed("", ""), -1.0);
    TEST_PASSED;
}

TEST(nonexistent_media2) {
    CHECK_ALMOST_EQUAL(total_time_viewed("a", "a"), -1.0);
    TEST_PASSED;
}

TEST(nonexistent_media3) {
    CHECK_CMP(add_media("a", 100.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.0, 100.0), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("a", ""), 0.0);
    clear_media();
    TEST_PASSED;
}

TEST(nonexistent_media4) {
    CHECK_CMP(add_media("a", 100.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.0, 100.0), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("", "Stan"), -1.0);
    clear_media();
    TEST_PASSED;
}

TEST(nonexistent_user) {
    CHECK_CMP(add_media("a", 100.0), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("a", "Stan"), 0.0);
    clear_media();
    TEST_PASSED;
}

TEST(nonexistent_user2) {
    CHECK_CMP(add_media("a", 100.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.0, 100.0), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("a", "Kyle"), 0.0);
    clear_media();
    TEST_PASSED;
}

TEST(zero_views) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 101.0), ==, 0);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0);
    clear_media();
    TEST_PASSED;
}

TEST(one_view) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 1.0), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 1.0);
    clear_media();
    TEST_PASSED;
}

TEST(one_plus_one_view) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 1.0), ==, 1);
    CHECK_CMP(add_media("y",1.0), ==, 1);
    CHECK_CMP(add_view("y", "Stan", 0.0, 0.5), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 1.0);
    CHECK_ALMOST_EQUAL(total_time_viewed("y", "Stan"), 0.5);
    clear_media();
    TEST_PASSED;
}

TEST(two_views_same_viewer) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.4), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.3);
    clear_media();
    TEST_PASSED;
}

TEST(one_valid_one_invalid) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 1.1), ==, 0);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.2);
    clear_media();
    TEST_PASSED;
}

TEST(two_viewers) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Kyle", 0.3, 0.8), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.2);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Kyle"), 0.5);
    clear_media();
    TEST_PASSED;
}

TEST(two_viewers_diff_media) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_media("y",10.0), ==, 1);
    CHECK_CMP(add_view("y", "Kyle", 0.3, 0.8), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.2);
    CHECK_ALMOST_EQUAL(total_time_viewed("y", "Stan"), 0.0);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Kyle"), 0.0);
    CHECK_ALMOST_EQUAL(total_time_viewed("y", "Kyle"), 0.5);
    clear_media();
    TEST_PASSED;
}

TEST(two_viewers_all_media) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Kyle", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_media("y",10.0), ==, 1);
    CHECK_CMP(add_view("y", "Kyle", 0.3, 0.8), ==, 1);
    CHECK_CMP(add_view("y", "Stan", 0.3, 0.8), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.2);
    CHECK_ALMOST_EQUAL(total_time_viewed("y", "Stan"), 0.5);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Kyle"), 0.2);
    CHECK_ALMOST_EQUAL(total_time_viewed("y", "Kyle"), 0.5);
    clear_media();
    TEST_PASSED;
}

TEST(two_then_clear_views) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Kyle", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_media("y",10.0), ==, 1);
    CHECK_CMP(add_view("y", "Kyle", 0.3, 0.8), ==, 1);
    CHECK_CMP(add_view("y", "Stan", 0.3, 0.8), ==, 1);
    clear_views();
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.0);
    CHECK_ALMOST_EQUAL(total_time_viewed("y", "Stan"), 0.0);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Kyle"), 0.0);
    CHECK_ALMOST_EQUAL(total_time_viewed("y", "Kyle"), 0.0);
    clear_media();
    TEST_PASSED;
}

TEST(two_then_clear_media) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Kyle", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_media("y",10.0), ==, 1);
    CHECK_CMP(add_view("y", "Kyle", 0.3, 0.8), ==, 1);
    CHECK_CMP(add_view("y", "Stan", 0.3, 0.8), ==, 1);
    clear_media();
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), -1.0);
    CHECK_ALMOST_EQUAL(total_time_viewed("y", "Stan"), -1.0);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Kyle"), -1.0);
    CHECK_ALMOST_EQUAL(total_time_viewed("y", "Kyle"), -1.0);
    clear_media();
    TEST_PASSED;
}

TEST(two_overlapping_views) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.5), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.5);
    clear_media();
    TEST_PASSED;
}

TEST(three_overlapping_views) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.5), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.6), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.6);
    clear_media();
    TEST_PASSED;
}

TEST(three_overlapping_views_s2) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.6), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.5), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.6);
    clear_media();
    TEST_PASSED;
}

TEST(three_overlapping_views2) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.7), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.2, 0.5), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.4), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.6);
    clear_media();
    TEST_PASSED;
}

TEST(three_overlapping_views2_s2) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.7), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.4), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.2, 0.5), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.6);
    clear_media();
    TEST_PASSED;
}

TEST(three_disjoint) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.5), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.55, 0.75), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.5);
    clear_media();
    TEST_PASSED;
}

TEST(three_disjoint_s2) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.55, 0.75), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.5), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.5);
    clear_media();
    TEST_PASSED;
}

TEST(two_overlapping_one_disjoint) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.3), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.2, 0.5), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.55, 0.75), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.6);
    clear_media();
    TEST_PASSED;
}

TEST(two_overlapping_one_disjoint_s2) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.3), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.55, 0.75), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.2, 0.5), ==, 1);
    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), 0.6);
    clear_media();
    TEST_PASSED;
}

TEST(many_overlapping_views) {
    CHECK_CMP(add_media("x", 100.0), ==, 1);
    static const int n = 1234;
    for (int i = 0; i < n; ++i)
	CHECK_CMP(add_view("x", "Stan", i*50.0/n, i*50.0/n + 10.0 + i*10.0/n), ==, 1);

    CHECK_ALMOST_EQUAL(total_time_viewed("x", "Stan"), (n-1)*60.0/n + 10.0);
    clear_media();
    TEST_PASSED;
}

TEST(one_media_many_views) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "user%d", i);
	CHECK_CMP(add_view("x", buf, 0.0, 0.2), ==, 1);
    }
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "user%d", i);
	CHECK_ALMOST_EQUAL(total_time_viewed("x", buf), 0.2);
    }
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "user%d", i);
	CHECK_CMP(add_view("x", buf, 0.1, 0.5), ==, 1);
    }
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "user%d", i);
	CHECK_ALMOST_EQUAL(total_time_viewed("x", buf), 0.5);
    }
    clear_media();
    TEST_PASSED;
}

TEST(one_media_many_views_clear) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "user%d", i);
	CHECK_CMP(add_view("x", buf, 0.0, 0.2), ==, 1);
    }
    clear_views();
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "user%d", i);
	CHECK_ALMOST_EQUAL(total_time_viewed("x", buf), 0.0);
    }
    TEST_PASSED;
}

TEST(one_view_many_media) {
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "media%d", i);
	CHECK_CMP(add_media(buf,1.0), ==, 1);
	CHECK_CMP(add_view(buf, "Stan", 0.0, 0.2), ==, 1);
    }
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "media%d", i);
	CHECK_CMP(add_view(buf, "Stan", 0.1, 0.5), ==, 1);
    }
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "media%d", i);
	CHECK_ALMOST_EQUAL(total_time_viewed(buf, "Stan"), 0.5);
    }
    clear_media();
    TEST_PASSED;
}

TEST(one_views_many_media_clear) {
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "media%d", i);
	CHECK_CMP(add_media(buf,1.0), ==, 1);
	CHECK_CMP(add_view(buf, "Stan", 0.0, 0.2), ==, 1);
    }
    clear_views();
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "media%d", i);
	CHECK_ALMOST_EQUAL(total_time_viewed(buf, "Stan"), 0.0);
    }
    clear_media();
    TEST_PASSED;
}

TEST(one_views_many_media_clear_media) {
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "media%d", i);
	CHECK_CMP(add_media(buf,1.0), ==, 1);
	CHECK_CMP(add_view(buf, "Stan", 0.0, 0.2), ==, 1);
    }
    clear_media();
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "media%d", i);
	CHECK_ALMOST_EQUAL(total_time_viewed(buf, "Antoonio"), -1.0);
    }
    TEST_PASSED;
}

MAIN_TEST_DRIVER(nonexistent_media,
		 nonexistent_media2,
		 nonexistent_media3,
		 nonexistent_media4,
		 nonexistent_user,
		 nonexistent_user2,
		 zero_views,
		 one_view,
		 one_plus_one_view,
		 two_views_same_viewer,
		 one_valid_one_invalid,
		 two_viewers,
		 two_viewers_diff_media,
		 two_viewers_all_media,
		 two_then_clear_views,
		 two_then_clear_media,
		 two_overlapping_views,
		 three_overlapping_views,
		 three_overlapping_views_s2,
		 three_overlapping_views2,
		 three_overlapping_views2_s2,
		 three_disjoint,
		 three_disjoint_s2,
		 two_overlapping_one_disjoint,
		 two_overlapping_one_disjoint_s2,
		 many_overlapping_views,
		 one_media_many_views,
		 one_media_many_views_clear,
		 one_view_many_media,
		 one_views_many_media_clear,
		 one_views_many_media_clear_media)
		 
