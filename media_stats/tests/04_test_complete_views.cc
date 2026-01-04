#include <cstdio>

#include "basic_testing.h"

#include "../media_stats.h"

TEST(nonexistent_media) {
    CHECK_CMP(complete_views(""), ==, -1);
    TEST_PASSED;
}

TEST(nonexistent_media2) {
    CHECK_CMP(complete_views("a"), ==, -1);
    TEST_PASSED;
}

TEST(nonexistent_media3) {
    CHECK_CMP(add_media("a", 100.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.0, 100.0), ==, 1);
    CHECK_CMP(complete_views(""), ==, -1);
    clear_media();
    TEST_PASSED;
}

TEST(nonexistent_media4) {
    CHECK_CMP(add_media("a", 100.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.0, 100.0), ==, 1);
    CHECK_CMP(complete_views("aa"), ==, -1);
    clear_media();
    TEST_PASSED;
}

TEST(nonexistent_user) {
    CHECK_CMP(add_media("a", 100.0), ==, 1);
    CHECK_CMP(complete_views("a"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(nonexistent_user2) {
    CHECK_CMP(add_media("a", 100.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.0, 100.0), ==, 1);
    CHECK_CMP(add_media("b", 100.0), ==, 1);
    CHECK_CMP(complete_views("b"), ==, 0.0);
    clear_media();
    TEST_PASSED;
}

TEST(zero_views) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 101.0), ==, 0);
    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(one_complete) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 1.0), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(one_incomplete) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.99), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(one_plus_one_view) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 1.0), ==, 1);
    CHECK_CMP(add_media("y",1.0), ==, 1);
    CHECK_CMP(add_view("y", "Stan", 0.0, 0.5), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 1);
    CHECK_CMP(complete_views("y"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(two_views_same_viewer) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.7), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 1.0), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(one_valid_one_invalid) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.7), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 1.1), ==, 0);
    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(two_incomplete) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Kyle", 0.3, 0.8), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(two_viewers_diff_media) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_media("y",10.0), ==, 1);
    CHECK_CMP(add_view("y", "Kyle", 0.3, 0.8), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 0);
    CHECK_CMP(complete_views("y"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(two_viewers_all_media) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Kyle", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_media("y",10.0), ==, 1);
    CHECK_CMP(add_view("y", "Kyle", 0.0, 10.0), ==, 1);
    CHECK_CMP(add_view("y", "Stan", 0.0, 10.0), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 0);
    CHECK_CMP(complete_views("y"), ==, 2);
    clear_media();
    TEST_PASSED;
}

TEST(two_then_clear_views) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Kyle", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_media("y",10.0), ==, 1);
    CHECK_CMP(add_view("y", "Kyle", 0.0, 10.0), ==, 1);
    CHECK_CMP(add_view("y", "Stan", 0.0, 10.0), ==, 1);
    clear_views();
    CHECK_CMP(complete_views("x"), ==, 0);
    CHECK_CMP(complete_views("y"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(two_then_clear_media) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Kyle", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_media("y",10.0), ==, 1);
    CHECK_CMP(add_view("y", "Kyle", 0.0, 10.0), ==, 1);
    CHECK_CMP(add_view("y", "Stan", 0.0, 10.0), ==, 1);
    clear_media();
    CHECK_CMP(complete_views("x"), ==, -1);
    CHECK_CMP(complete_views("y"), ==, -1);
    clear_media();
    TEST_PASSED;
}

TEST(two_overlapping_views) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.5), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(three_overlapping_views) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.5), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.6), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(three_overlapping_views_s2) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.6), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.1, 0.5), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(three_overlapping_complete) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.4), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.6), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.6, 1.0), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(three_overlapping_complete_s2) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.6), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.4), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.6, 1.0), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(three_overlapping_views2) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.01, 0.99), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.2, 0.5), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.4), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(three_disjoint) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.2), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.3, 0.5), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.55, 1.0), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(two_overlapping_one_disjoint) {
    CHECK_CMP(add_media("x",1.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.0, 0.3), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.2, 0.5), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 0.55, 1.0), ==, 1);
    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(many_overlapping_incomplete) {
    CHECK_CMP(add_media("x", 100.0), ==, 1);
    static const int n = 1234;
    for (int i = 0; i < n; ++i) 
	CHECK_CMP(add_view("x", "Stan", i*50.0/n, i*50.0/n + 10.0 + i*10.0/n), ==, 1);

    CHECK_CMP(complete_views("x"), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(many_overlapping_complete) {
    CHECK_CMP(add_media("x", 100.0), ==, 1);
    static const int n = 1234;
    for (int i = 0; i < n; ++i) 
	CHECK_CMP(add_view("x", "Stan", i*50.0/n, i*50.0/n + 10.0 + i*10.0/n), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 50.0, 70.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 70.0, 90.0), ==, 1);
    CHECK_CMP(add_view("x", "Stan", 80.0, 100.0), ==, 1);

    CHECK_CMP(complete_views("x"), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(many_users_many_overlapping_complete) {
    CHECK_CMP(add_media("x", 100.0), ==, 1);
    static const int n = 30;
    for (int j = 0; j < 1234; ++j) {
	char buf[20];
	sprintf(buf, "user%d", j);
	for (int i = 0; i < n; ++i) 
	    CHECK_CMP(add_view("x", buf, i*50.0/n, i*50.0/n + 10.0 + i*10.0/n), ==, 1);
	CHECK_CMP(add_view("x", buf, 50.0, 70.0), ==, 1);
	CHECK_CMP(add_view("x", buf, 70.0, 90.0), ==, 1);
	CHECK_CMP(add_view("x", buf, 80.0, 100.0), ==, 1);
    }
    CHECK_CMP(complete_views("x"), ==, 1234);
    clear_media();
    TEST_PASSED;
}

TEST(many_users_many_overlapping_incomplete) {
    CHECK_CMP(add_media("x", 100.0), ==, 1);
    static const int n = 30;
    for (int j = 0; j < 1234; ++j) {
	char buf[20];
	sprintf(buf, "user%d", j);
	for (int i = 0; i < n; ++i) 
	    CHECK_CMP(add_view("x", buf, i*50.0/n, i*50.0/n + 10.0 + i*10.0/n), ==, 1);
	CHECK_CMP(add_view("x", buf, 50.0, 70.0), ==, 1);
	CHECK_CMP(add_view("x", buf, 80.0, 100.0), ==, 1);
    }
    CHECK_CMP(complete_views("x"), ==, 0);
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
    CHECK_CMP(complete_views("x"), ==, 0);
    for (int i = 1200; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "user%d", i);
	CHECK_CMP(add_view("x", buf, 0.1, 1.0), ==, 1);
    }
    CHECK_CMP(complete_views("x"), ==, 1234 - 1200);
    clear_media();
    TEST_PASSED;
}

MAIN_TEST_DRIVER(nonexistent_media,
		 nonexistent_media2,
		 nonexistent_media3,
		 nonexistent_media4,
		 nonexistent_user,
		 nonexistent_user2,
		 zero_views,
		 one_complete,
		 one_incomplete,
		 one_plus_one_view,
		 two_views_same_viewer,
		 one_valid_one_invalid,
		 two_incomplete,
		 two_viewers_diff_media,
		 two_viewers_all_media,
		 two_then_clear_views,
		 two_then_clear_media,
		 two_overlapping_views,
		 three_overlapping_views,
		 three_overlapping_views_s2,
		 three_overlapping_complete,
		 three_overlapping_complete_s2,
		 three_overlapping_views2,
		 three_disjoint,
		 two_overlapping_one_disjoint,
		 many_overlapping_incomplete,
		 many_overlapping_complete,
		 many_users_many_overlapping_complete,
		 many_users_many_overlapping_incomplete,
		 one_media_many_views)
		 
		 
