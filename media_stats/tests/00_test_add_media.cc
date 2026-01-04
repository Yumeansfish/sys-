#include "basic_testing.h"

#include "../media_stats.h"

TEST(add_empty) {
    CHECK_CMP(add_media("",1.0), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(add_two) {
    CHECK_CMP(add_media("a",1.0), ==, 1);
    CHECK_CMP(add_media("b",2.0), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(add_three) {
    CHECK_CMP(add_media("c",2.0), ==, 1);
    CHECK_CMP(add_media("cc",2.0), ==, 1);
    CHECK_CMP(add_media("ccc",2.0), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(invalid_duplicate) {
    CHECK_CMP(add_media("a", 1.0), ==, 1);
    CHECK_CMP(add_media("a", 1.5), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(invalid_duplicate2) {
    CHECK_CMP(add_media("a", 1.0), ==, 1);
    CHECK_CMP(add_media("b", 1.0), ==, 1);
    CHECK_CMP(add_media("a", 1.0), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(invalid_duplicate_empty) {
    CHECK_CMP(add_media("",1.0), ==, 1);
    CHECK_CMP(add_media("",1.0), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(invalid_duplicate_empty2) {
    CHECK_CMP(add_media("",1.0), ==, 1);
    CHECK_CMP(add_media("a",1.0), ==, 1);
    CHECK_CMP(add_media("",1.0), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(invalid_duration) {
    CHECK_CMP(add_media("a",-1.0), ==, 0);
    CHECK_CMP(add_media("a", 0.0), ==, 0);
    clear_media();
    TEST_PASSED;
}

TEST(weird_titles) {
    CHECK_CMP(add_media("abcdefghijklmnopqrstuvwxyz 0123456789-+_=/?.>,<;:'\"[{]}\\|!@#$%^&*()~`", 1.0), ==, 1);
    CHECK_CMP(add_media("abcdefghijklmnopqrstuvwxyz 0123456789-+_=/?.>,<;:'\"[{]}\\|!@#$%^&*()~`abcdefghijklmnopqrstuvwxyz 0123456789-+_=/?.>,<;:'\"[{]}\\|!@#$%^&*()~`abcdefghijklmnopqrstuvwxyz 0123456789-+_=/?.>,<;:'\"[{]}\\|!@#$%^&*()~`abcdefghijklmnopqrstuvwxyz 0123456789-+_=/?.>,<;:'\"[{]}\\|!@#$%^&*()~`abcdefghijklmnopqrstuvwxyz 0123456789-+_=/?.>,<;:'\"[{]}\\|!@#$%^&*()~`abcdefghijklmnopqrstuvwxyz 0123456789-+_=/?.>,<;:'\"[{]}\\|!@#$%^&*()~`abcdefghijklmnopqrstuvwxyz 0123456789-+_=/?.>,<;:'\"[{]}\\|!@#$%^&*()~`abcdefghijklmnopqrstuvwxyz 0123456789-+_=/?.>,<;:'\"[{]}\\|!@#$%^&*()~`", 2.0), ==, 1);
    clear_media();
    TEST_PASSED;
}

TEST(different_strings_same_buffer) {
    char buf[10];
    buf[0] = 'a'; buf[1] = '\0';
    CHECK_CMP(add_media(buf,1.0), ==, 1);
    buf[0] = 'b'; buf[1] = '\0';
    CHECK_CMP(add_media(buf,2.0), ==, 1);
    buf[0] = 'c'; buf[1] = '\0';
    CHECK_CMP(unique_viewers(buf), ==, -1);
    CHECK_CMP(unique_viewers("c"), ==, -1);
    CHECK_CMP(unique_viewers("a"), ==, 0);
    CHECK_CMP(unique_viewers("b"), ==, 0);
    clear_media();
    TEST_PASSED;
}

MAIN_TEST_DRIVER(add_empty,
		 add_two,
		 add_three,
		 invalid_duplicate,
		 invalid_duplicate2,
		 invalid_duplicate_empty,
		 invalid_duplicate_empty2,
		 invalid_duration,
		 weird_titles,
		 different_strings_same_buffer)
    
