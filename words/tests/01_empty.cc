#include "basic_testing.h"
#include "../words.h"

TEST (create) {
    lines * l = lines_create();
    CHECK (l != nullptr);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_empty_match_0) {
    lines * l = lines_create();
    CHECK (l != nullptr);
    add_line (l, "");
    const char * output[10];
    CHECK (match (l, output, 10, "") == 0);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_empty_match_1) {
    lines * l = lines_create();
    CHECK (l != nullptr);
    add_line (l, "");
    const char * output[10];
    CHECK (match (l, output, 10, "one") == 0);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_empty_match_2) {
    lines * l = lines_create();
    CHECK (l != nullptr);
    add_line (l, "");
    const char * output[10];
    CHECK (match (l, output, 10, "one two") == 0);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (one_line_empty_match_3) {
    lines * l = lines_create();
    CHECK (l != nullptr);
    add_line (l, "");
    const char * output[10];
    CHECK (match (l, output, 10, "one two three") == 0);
    lines_destroy (l);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
