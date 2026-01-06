#include <cstdio>

#include "basic_testing.h"

#include "../snake.h"

TEST (right_line) {
    struct snake * s = snake_new (100, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    for (int i = 0; i < 99; ++i)
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (down_line) {
    struct snake * s = snake_new (100, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int i = 0; i < 9; ++i)
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (two_right_down) {
    struct snake * s1 = snake_new (100, 10, 5);
    CHECK_CMP (s1,!=,nullptr);
    CHECK_CMP (snake_start (s1, 0, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    struct snake * s2 = snake_new (100, 10, 5);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_start (s2, 0, 0, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int i = 0; i < 99; ++i)
	CHECK_CMP (snake_step (s1),==,SNAKE_OKAY);
    for (int i = 0; i < 9; ++i)
	CHECK_CMP (snake_step (s2),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s1),==,SNAKE_OKAY);
    CHECK_CMP (snake_get_status (s2),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s1),==,SNAKE_FAIL);
    CHECK_CMP (snake_step (s2),==,SNAKE_FAIL);
    snake_destroy (s1);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (down_right_d) {
    struct snake * s = snake_new (100, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int i = 0; i < 9; ++i) {
	CHECK_CMP (snake_change_direction (s, SNAKE_RIGHT),==,SNAKE_OKAY);
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_DOWN),==,SNAKE_OKAY);
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    }
    CHECK_CMP (snake_change_direction (s, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_change_direction (s, SNAKE_DOWN),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (circle_simple) {
    struct snake * s = snake_new (100, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_DOWN),==,SNAKE_OKAY);
    CHECK_CMP (snake_change_direction (s, SNAKE_RIGHT),==,SNAKE_OKAY);
    for (int i = 0; i < 99; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_change_direction (s, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int i = 0; i < 9; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_change_direction (s, SNAKE_LEFT),==,SNAKE_OKAY);
    for (int i = 0; i < 99; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_change_direction (s, SNAKE_UP),==,SNAKE_OKAY);
    for (int i = 0; i < 9; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (ten_circles_simple) {
    struct snake * s = snake_new (100, 10, 5);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int j = 0; j < 10; ++j) {
	CHECK_CMP (snake_change_direction (s, SNAKE_RIGHT),==,SNAKE_OKAY);
	for (int i = 0; i < 99; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_DOWN),==,SNAKE_OKAY);
	for (int i = 0; i < 9; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_LEFT),==,SNAKE_OKAY);
	for (int i = 0; i < 99; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_UP),==,SNAKE_OKAY);
	for (int i = 0; i < 9; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    }
    snake_destroy (s);
    TEST_PASSED;
}

TEST (ten_circles_simple_border) {
    struct snake * s = snake_new (100, 10, 100);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int j = 0; j < 10; ++j) {
	CHECK_CMP (snake_change_direction (s, SNAKE_RIGHT),==,SNAKE_OKAY);
	for (int i = 0; i < 99; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_DOWN),==,SNAKE_OKAY);
	for (int i = 0; i < 9; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_LEFT),==,SNAKE_OKAY);
	for (int i = 0; i < 99; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_UP),==,SNAKE_OKAY);
	for (int i = 0; i < 9; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    }
    snake_destroy (s);
    TEST_PASSED;
}

TEST (ten_circles_simple_almost_full) {
    struct snake * s = snake_new (100, 10, 200);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int j = 0; j < 10; ++j) {
	CHECK_CMP (snake_change_direction (s, SNAKE_RIGHT),==,SNAKE_OKAY);
	for (int i = 0; i < 99; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_DOWN),==,SNAKE_OKAY);
	for (int i = 0; i < 9; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_LEFT),==,SNAKE_OKAY);
	for (int i = 0; i < 99; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_UP),==,SNAKE_OKAY);
	for (int i = 0; i < 9; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    }
    snake_destroy (s);
    TEST_PASSED;
}

TEST (ten_circles_simple_full) {
    struct snake * s = snake_new (100, 10, 216);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int j = 0; j < 10; ++j) {
	CHECK_CMP (snake_change_direction (s, SNAKE_RIGHT),==,SNAKE_OKAY);
	for (int i = 0; i < 99; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_DOWN),==,SNAKE_OKAY);
	for (int i = 0; i < 9; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_LEFT),==,SNAKE_OKAY);
	for (int i = 0; i < 99; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	CHECK_CMP (snake_change_direction (s, SNAKE_UP),==,SNAKE_OKAY);
	for (int i = 0; i < 9; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    }
    snake_destroy (s);
    TEST_PASSED;
}

TEST (spiral) {
    const int r = 10;
    const int c = 100;
    struct snake * s = snake_new (c, r, c*r);
    CHECK_CMP (s,!=,nullptr);
    int x = c;
    int y = r;
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    if (x > 1) {
	for (int i = 1; i < x; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    }
    for (;;) {
	if (y <= 1)
	    break;
	snake_change_direction (s, SNAKE_DOWN);
	for (int i = 1; i < y; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	--y;
	if (x <= 1)
	    break;
	snake_change_direction (s, SNAKE_LEFT);
	for (int i = 1; i < x; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	--x;
	if (y <= 1)
	    break;
	snake_change_direction (s, SNAKE_UP);
	for (int i = 1; i < y; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	--y;
	if (x <= 1)
	    break;
	snake_change_direction (s, SNAKE_RIGHT);
	for (int i = 1; i < x; ++i) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	--x;
    }
    snake_destroy (s);
    TEST_PASSED;
}

TEST (down_up) {
    const int r = 10;
    const int c = 100;
    struct snake * s = snake_new (c, r, c*r);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_DOWN),==,SNAKE_OKAY);
    int d = SNAKE_DOWN;
    int i = 1;
    for (;;) {
	for (int j = 1; j < r; ++j) 
	    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	if (i == c)
	    break;
	++i;
	snake_change_direction (s, SNAKE_RIGHT);
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
	d = (d == SNAKE_DOWN) ? SNAKE_UP : SNAKE_DOWN;
	snake_change_direction (s, d);
    }
    snake_destroy (s);
    TEST_PASSED;
}

TEST (back_and_forth_down) {
    struct snake * s = snake_new (100, 100, 30);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_UP);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (back_and_forth_up) {
    struct snake * s = snake_new (100, 100, 30);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_UP),==,SNAKE_OKAY);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_DOWN);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (back_and_forth_right) {
    struct snake * s = snake_new (100, 100, 30);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_RIGHT),==,SNAKE_OKAY);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (back_and_forth_left) {
    struct snake * s = snake_new (100, 100, 30);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_LEFT),==,SNAKE_OKAY);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_RIGHT);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (not_crossing_up) {
    struct snake * s = snake_new (100, 100, 30);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_RIGHT),==,SNAKE_OKAY);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_DOWN);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_UP);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (crossing_up) {
    struct snake * s = snake_new (100, 100, 40);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_RIGHT),==,SNAKE_OKAY);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_DOWN);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_UP);
    for (int i = 1; i < 9; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (not_crossing_up_barely) {
    struct snake * s = snake_new (100, 100, 36);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_RIGHT),==,SNAKE_OKAY);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_DOWN);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_UP);
    for (int i = 1; i < 20; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (tight_crossing_up) {
    struct snake * s = snake_new (100, 100, 10);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_DOWN);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_UP);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (tight_not_crossing_up) {
    struct snake * s = snake_new (100, 100, 4);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_DOWN);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_UP);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (crossing_ell) {
    struct snake * s = snake_new (100, 100, 29);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_RIGHT);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_DOWN);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    for (int i = 1; i < 11; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_UP);
    for (int i = 1; i < 5; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_RIGHT);
    CHECK_CMP (snake_step (s),==,SNAKE_FAIL);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (not_crossing_ell) {
    struct snake * s = snake_new (100, 100, 28);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 50, 50, SNAKE_DOWN),==,SNAKE_OKAY);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_RIGHT);
    for (int i = 1; i < 10; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_DOWN);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    for (int i = 1; i < 11; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_UP);
    for (int i = 1; i < 5; ++i) 
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_RIGHT);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_destroy (s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER ();
