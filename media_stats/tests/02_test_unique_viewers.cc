#include <cstdio>

#include "basic_testing.h"

#include "../media_stats.h"

TEST(nonexistent_media) {
    CHECK_CMP(unique_viewers(""), ==, -1);
    TEST_PASSED;
}

TEST(nonexistent_media2) {
    CHECK_CMP(unique_viewers("a"), ==, -1);
    TEST_PASSED;
}

TEST(nonexistent_media3) {
    CHECK_CMP(add_media("a",1.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.0, 1.0), ==, 1);
    CHECK_CMP(unique_viewers(""), ==, -1);
    clear_media();
    TEST_PASSED;
}

TEST(nonexistent_media4) {
    CHECK_CMP(add_media("",1.0), ==, 1);
    CHECK_CMP(add_view("", "Stan", 0.0, 1.0), ==, 1);
    CHECK_CMP(unique_viewers("a"), ==, -1);
    clear_media();
    TEST_PASSED;
}

TEST(zero_views) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(unique_viewers("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(one_view) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 1.0), ==, 1);
    CHECK_CMP(unique_viewers("x"), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(one_plus_one_view) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 1.0), ==, 1);
    CHECK_CMP(add_media("y",1.0), ==, 1);
    CHECK_CMP(add_view("y", "Stan", 0.0, 1.0), ==, 1);
    CHECK_CMP(unique_viewers("x"), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(two_views_same_viewer) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.4), ==, 1);
    CHECK_CMP(unique_viewers("x"), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(one_valid_one_invalid) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Kyle", 0.3, 1.1), ==, 0);
    CHECK_CMP(unique_viewers("x"), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(two_viewers) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Kyle", 0.3, 0.8), ==, 1);
    CHECK_CMP(unique_viewers("x"), ==, 2);
    clear_media();
    TEST_PASSED;
}

TEST(two_viewers_diff_media) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_media("y",10.0), ==, 1);
    CHECK_CMP(add_view("y", "Kyle", 0.3, 0.8), ==, 1);
    CHECK_CMP(unique_viewers("x"), ==, 1);
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
    CHECK_CMP(unique_viewers("x"), ==, 2);
    CHECK_CMP(unique_viewers("y"), ==, 2);
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
    CHECK_CMP(unique_viewers("x"), ==, 0);
    CHECK_CMP(unique_viewers("y"), ==, 0);
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
    CHECK_CMP(unique_viewers("x"), ==, -1);
    CHECK_CMP(unique_viewers("y"), ==, -1);
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
    CHECK_CMP(unique_viewers("x"), ==, 1234);
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "user%d", i);
	CHECK_CMP(add_view("x", buf, 0.1, 0.5), ==, 1);
    }
    CHECK_CMP(unique_viewers("x"), ==, 1234);
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
    CHECK_CMP(unique_viewers("x"), ==, 0);
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
	CHECK_CMP(unique_viewers(buf), ==, 1);
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
	CHECK_CMP(unique_viewers(buf), ==, 0);
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
	CHECK_CMP(unique_viewers(buf), ==, -1);
    }
    TEST_PASSED;
}

MAIN_TEST_DRIVER(nonexistent_media,
		 nonexistent_media2,
		 nonexistent_media3,
		 nonexistent_media4,
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
		 one_media_many_views,
		 one_media_many_views_clear,
		 one_view_many_media,
		 one_views_many_media_clear,
		 one_views_many_media_clear_media)
		 
		 
