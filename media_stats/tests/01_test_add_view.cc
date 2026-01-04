#include "basic_testing.h"

#include "../media_stats.h"

TEST(nonexistent_media) {
    CHECK_CMP(add_view("", "Stan", 0.0, 1.0), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(nonexistent_media2) {
    CHECK_CMP(add_view("Stan", "Stan", 0.0, 1.0), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(bad_title) {
    CHECK_CMP(add_media("a",1.0), ==, 1);
    CHECK_CMP(add_view("", "Stan", 0.0, 1.0), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(bad_title2) {
    CHECK_CMP(add_media("a",1.0), ==, 1);
    CHECK_CMP(add_view("aa", "Stan", 0.0, 1.0), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(first_full) {
    CHECK_CMP(add_media("a",1.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.0, 1.0), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(first_middle) {
    CHECK_CMP(add_media("a",10.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 1.0, 9.0), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(first_beginning) {
    CHECK_CMP(add_media("a",10.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.0, 9.0), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(first_end) {
    CHECK_CMP(add_media("a",10.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 1.0, 10.0), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(bad_negative_start) {
    CHECK_CMP(add_media("a",1.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", -1.0, 1.0), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(bad_finish_greater_than_duration) {
    CHECK_CMP(add_media("a",1.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.5, 1.1), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(bad_start_after_finish) {
    CHECK_CMP(add_media("a", 1.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.5, 0.4), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(bad_start_same_as_finish) {
    CHECK_CMP(add_media("a", 1.0), ==, 1);
    CHECK_CMP(add_view("a", "Stan", 0.5, 0.5), ==, 0);
    clear_media();
    TEST_PASSED;
}

MAIN_TEST_DRIVER(nonexistent_media,
		 nonexistent_media2,
		 bad_title,
		 bad_title2,
		 first_full,
		 first_middle,
		 first_beginning,
		 first_end,
		 bad_negative_start,
		 bad_finish_greater_than_duration,
		 bad_start_after_finish,
		 bad_start_same_as_finish)
		 
		 
