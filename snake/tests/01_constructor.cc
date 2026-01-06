#include <cstdio>

#include "basic_testing.h"

#include "../snake.h"

TEST (construct_1) {
    struct snake * s = snake_new (1, 1, 1);
    CHECK_CMP (s,!=,nullptr);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (construct_10) {
    struct snake * s = snake_new (10, 10, 10);
    CHECK_CMP (s,!=,nullptr);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (construct_1000) {
    struct snake * s = snake_new (1000, 1000, 10000);
    CHECK_CMP (s,!=,nullptr);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (construct_1000_2000) {
    struct snake * s1 = snake_new (1000, 1000, 10000);
    CHECK_CMP (s1,!=,nullptr);
    struct snake * s2 = snake_new (2000, 2000, 20000);
    CHECK_CMP (s2,!=,nullptr);
    snake_destroy (s2);
    TEST_PASSED;
}

MAIN_TEST_DRIVER ();
		  
