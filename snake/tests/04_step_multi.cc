#include <cstdio>

#include "basic_testing.h"

#include "../snake.h"

TEST (basic_single) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 5, 5, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_up_okay) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 5, 5, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_up_okay_border) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 5, 1, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_up_fail) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 5, 0, SNAKE_UP),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_down_okay) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 5, 5, SNAKE_DOWN),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_down_okay_border) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 5, 8, SNAKE_DOWN),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_down_fail) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 5, 9, SNAKE_DOWN),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_right_okay) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 5, 5, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_right_okay_border) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 8, 5, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_right_fail) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 9, 5, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_left_okay) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 5, 5, SNAKE_LEFT),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_left_okay_border) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 1, 5, SNAKE_LEFT),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (one_left_fail) {
    struct snake * s = snake_new (10, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    struct snake * s2 = snake_new (10, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s2, 5, 5, SNAKE_UP),==,SNAKE_OKAY);

    CHECK_CMP (snake_get_status (s),==,SNAKE_NEW);
    CHECK_CMP (snake_start (s, 0, 5, SNAKE_LEFT),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    CHECK_CMP (snake_get_status (s),==,SNAKE_FAIL);
    snake_destroy (s);
    snake_destroy (s2);
    TEST_PASSED;
}

MAIN_TEST_DRIVER ();
