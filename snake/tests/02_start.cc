#include <cstdio>

#include "basic_testing.h"

#include "../snake.h"

TEST (init_state) {
    struct snake * s = snake_new (1000, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (started_state) {
    struct snake * s = snake_new (1000, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 500, 500, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (start_corner_ul) {
    struct snake * s = snake_new (1000, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_LEFT),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (start_corner_ur) {
    struct snake * s = snake_new (1000, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 999, 0, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (start_corner_dl) {
    struct snake * s = snake_new (1000, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 999, SNAKE_DOWN),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (start_corner_dr) {
    struct snake * s = snake_new (1000, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 999, 999, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (failed_start_direction_0) {
    struct snake * s = snake_new (1000, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 500, 500, 0),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (failed_start_direction_5) {
    struct snake * s = snake_new (1000, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 500, 500, 5),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (failed_start_column) {
    struct snake * s = snake_new (200, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 500, 500, SNAKE_UP),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (failed_start_column_negative) {
    struct snake * s = snake_new (200, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, -1, 500, SNAKE_UP),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (failed_start_column_limit) {
    struct snake * s = snake_new (200, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 200, 500, SNAKE_UP),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (failed_start_row) {
    struct snake * s = snake_new (1000, 200, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 500, 500, SNAKE_UP),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (failed_start_row_negative) {
    struct snake * s = snake_new (1000, 200, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 500, -1, SNAKE_UP),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (failed_start_row_limit) {
    struct snake * s = snake_new (1000, 200, 10000);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 500, 200, SNAKE_UP),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (init_state_two) {
    struct snake * s1 = snake_new (1000, 1000, 10000);
    struct snake * s2 = snake_new (1000, 1000, 10000);
    CHECK_CMP (s1,!=,nullptr);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_NEW);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s1, 500, 500, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 300, 300, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_OKAY);
    snake_destroy (s1);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (init_state_two_reset) {
    struct snake * s1 = snake_new (1000, 1000, 10000);
    struct snake * s2 = snake_new (1000, 1000, 10000);
    CHECK_CMP (s1,!=,nullptr);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_NEW);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s1, 500, 500, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 300, 300, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_OKAY);
    CHECK_CMP (snake_start (s1, 200, 200, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_OKAY);
    CHECK_CMP (snake_start (s2, 100, 100, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_OKAY);
    snake_destroy (s1);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (init_state_two_reset_one_fail) {
    struct snake * s1 = snake_new (1000, 1000, 10000);
    struct snake * s2 = snake_new (500, 500, 10000);
    CHECK_CMP (s1,!=,nullptr);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_NEW);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s1, 500, 500, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 300, 300, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_OKAY);
    CHECK_CMP (snake_start (s1, 300, 300, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_OKAY);
    CHECK_CMP (snake_start (s2, 500, 500, SNAKE_UP),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_FAIL);
    CHECK_CMP (snake_start (s2, 499, 499, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_OKAY);
    snake_destroy (s1);
    snake_destroy (s2);
    TEST_PASSED;
}

MAIN_TEST_DRIVER ();
		  
