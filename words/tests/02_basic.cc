#include "basic_testing.h"
#include "../words.h"

TEST (one_line_no_match) {
    lines * l = lines_create();
    add_line (l, "one two three");
    const char * output[10];
    CHECK (match (l, output, 10, "") == 0);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_simple_match) {
    lines * l = lines_create();
    add_line (l, "one two three");
    const char * output[10];
    CHECK (match (l, output, 10, "two") == 1);
    CHECK_STRING_CMP (output[0],==,"one two three");
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_no_match_erased_buffer) {
    lines * l = lines_create();
    char buf[100] = "one two three";
    add_line (l, buf);
    buf[0] = 0;
    const char * output[10];
    CHECK (match (l, output, 10, "two") == 1);
    CHECK_STRING_CMP (output[0],==,"one two three");
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_double_match) {
    lines * l = lines_create();
    add_line (l, "one two three");
    const char * output[10];
    CHECK (match (l, output, 10, "one two") == 1);
    CHECK_STRING_CMP (output[0],==,"one two three");
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_double_match_reverse) {
    lines * l = lines_create();
    add_line (l, "one two three");
    const char * output[10];
    CHECK (match (l, output, 10, "two one") == 1);
    CHECK_STRING_CMP (output[0],==,"one two three");
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_double_match_sub) {
    lines * l = lines_create();
    add_line (l, "one two three");
    const char * output[10];
    CHECK (match (l, output, 10, "w re") == 1);
    CHECK_STRING_CMP (output[0],==,"one two three");
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_double_match_sub_reverse) {
    lines * l = lines_create();
    add_line (l, "one two three");
    const char * output[10];
    CHECK (match (l, output, 10, "w ne") == 1);
    CHECK_STRING_CMP (output[0],==,"one two three");
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_misc_sub) {
    lines * l = lines_create();
    add_line (l, "one two three");
    const char * output[10];
    CHECK (match (l, output, 10, "w ne t o re ee") == 1);
    CHECK_STRING_CMP (output[0],==,"one two three");
    lines_destroy (l);
    TEST_PASSED;
}

TEST (no_spaces_line_misc_sub) {
    lines * l = lines_create();
    add_line (l, "onetwothree");
    const char * output[10];
    CHECK (match (l, output, 10, "w ne t o re ee") == 1);
    CHECK_STRING_CMP (output[0],==,"onetwothree");
    lines_destroy (l);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
