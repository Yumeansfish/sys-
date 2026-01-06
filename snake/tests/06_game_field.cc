#include <cstdio>
#include <cstring>

#include "basic_testing.h"

#include "../snake.h"

TEST (init_line_begin) {
    struct snake * s = snake_new (10, 1, 5);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "@         ", 10) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (init_line_end) {
    struct snake * s = snake_new (10, 1, 5);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 9, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "         @", 10) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (line_moving_left_to_right_five) {
    struct snake * s = snake_new (10, 1, 5);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "@         ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "+@        ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "+#@       ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "+##@      ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "+###@     ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " +###@    ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "  +###@   ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "   +###@  ", 10) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (line_moving_left_to_right_one) {
    struct snake * s = snake_new (10, 1, 1);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "@         ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " @        ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "  @       ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "   @      ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "    @     ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "     @    ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "      @   ", 10) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (line_moving_back_and_forth_one) {
    struct snake * s = snake_new (10, 1, 1);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "@         ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " @        ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "  @       ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "   @      ", 10) == 0);
    snake_change_direction (s, SNAKE_LEFT);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "  @       ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " @        ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "@         ", 10) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (line_moving_left_to_right_two) {
    struct snake * s = snake_new (10, 1, 2);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "@         ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "+@        ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " +@       ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "  +@      ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "   +@     ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "    +@    ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "     +@   ", 10) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (line_moving_left_to_right_three) {
    struct snake * s = snake_new (10, 1, 3);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 0, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "@         ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "+@        ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "+#@       ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " +#@      ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "  +#@     ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "   +#@    ", 10) == 0);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "    +#@   ", 10) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (three_by_two_circle_6) {
    struct snake * s = snake_new (10, 2, 6);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 1, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " @        "
		                       "          ", 20) == 0);
    for (int i = 1; i < 3; ++i)
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " +#@      "
		                       "          ", 20) == 0);
    snake_change_direction (s, SNAKE_DOWN);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " +##      "
		                       "   @      ", 20) == 0);
    snake_change_direction (s, SNAKE_LEFT);
    for (int i = 1; i < 3; ++i)
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " +##      "
		                       " @##      ", 20) == 0);
    snake_change_direction (s, SNAKE_UP);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " @+#      "
		                       " ###      ", 20) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (three_by_two_circle_5_reset) {
    struct snake * s = snake_new (10, 2, 5);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 1, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " @        "
		                       "          ", 20) == 0);
    for (int i = 1; i < 3; ++i)
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " +#@      "
		                       "          ", 20) == 0);
    snake_change_direction (s, SNAKE_DOWN);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " +##      "
		                       "   @      ", 20) == 0);
    snake_change_direction (s, SNAKE_LEFT);
    for (int i = 1; i < 3; ++i)
	CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "  +#      "
		                       " @##      ", 20) == 0);
    snake_change_direction (s, SNAKE_UP);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), " @ +      "
		                       " ###      ", 20) == 0);
    CHECK_CMP (snake_start (s, 0, 1, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "          "
		                       "@         ", 20) == 0);

    CHECK_CMP (snake_start (s, 9, 1, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "          "
		                       "         @", 20) == 0);

    CHECK_CMP (snake_start (s, 9, 0, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "         @"
		                       "          ", 20) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (diagonal_5_by_5) {
    struct snake * s = snake_new (5, 5, 6);
    CHECK_CMP (s,!=,nullptr);
    CHECK_CMP (snake_start (s, 4, 4, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "     "
		                       "     "
		                       "     "
		                       "     "
		                       "    @", 25) == 0);
    snake_change_direction (s, SNAKE_UP);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "     "
		                       "     "
		                       "     "
		                       "   @#"
		                       "    +", 25) == 0);
    snake_change_direction (s, SNAKE_UP);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "     "
		                       "     "
		                       "  @# "
		                       "   ##"
		                       "    +", 25) == 0);
    snake_change_direction (s, SNAKE_UP);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    snake_change_direction (s, SNAKE_LEFT);
    CHECK_CMP (snake_step (s),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "     "
		                       " @#  "
		                       "  ## "
		                       "   #+"
		                       "     ", 25) == 0);

    CHECK_CMP (snake_start (s, 2, 3, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "     "
		                       "     "
		                       "     "
		                       "  @  "
		                       "     ", 25) == 0);

    CHECK_CMP (snake_start (s, 3, 2, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s), "     "
		                       "     "
		                       "   @ "
		                       "     "
		                       "     ", 25) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (multi_diagonal_5_by_5) {
    struct snake * s1 = snake_new (5, 5, 6);
    struct snake * s2 = snake_new (5, 5, 6);
    CHECK_CMP (s1,!=,nullptr);
    CHECK_CMP (s2,!=,nullptr);
    CHECK_CMP (snake_start (s1, 4, 4, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK_CMP (snake_start (s2, 3, 2, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s1), "     "
		                        "     "
		                        "     "
		                        "     "
		                        "    @", 25) == 0);
    CHECK (memcmp(snake_get_field (s2), "     "
		                        "     "
		                        "   @ "
		                        "     "
		                        "     ", 25) == 0);
    snake_change_direction (s2, SNAKE_UP);
    CHECK_CMP (snake_step (s2),==,SNAKE_OKAY);
    snake_change_direction (s2, SNAKE_LEFT);
    CHECK_CMP (snake_step (s2),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s1), "     "
		                        "     "
		                        "     "
		                        "     "
		                        "    @", 25) == 0);
    CHECK (memcmp(snake_get_field (s2), "     "
		                        "  @# "
		                        "   + "
		                        "     "
		                        "     ", 25) == 0);
    snake_change_direction (s1, SNAKE_UP);
    CHECK_CMP (snake_step (s1),==,SNAKE_OKAY);
    snake_change_direction (s1, SNAKE_LEFT);
    CHECK_CMP (snake_step (s1),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s1), "     "
 		                        "     "
		                        "     "
		                        "   @#"
		                        "    +", 25) == 0);
    snake_change_direction (s1, SNAKE_UP);
    CHECK_CMP (snake_step (s1),==,SNAKE_OKAY);
    snake_change_direction (s1, SNAKE_LEFT);
    CHECK_CMP (snake_step (s1),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s1), "     "
		                        "     "
		                        "  @# "
		                        "   ##"
		                        "    +", 25) == 0);
    CHECK (memcmp(snake_get_field (s2), "     "
		                        "  @# "
		                        "   + "
		                        "     "
		                        "     ", 25) == 0);
    snake_change_direction (s1, SNAKE_UP);
    CHECK_CMP (snake_step (s1),==,SNAKE_OKAY);
    snake_change_direction (s1, SNAKE_LEFT);
    CHECK_CMP (snake_step (s1),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s1), "     "
		                        " @#  "
		                        "  ## "
		                        "   #+"
		                        "     ", 25) == 0);
    CHECK (memcmp(snake_get_field (s2), "     "
		                        "  @# "
		                        "   + "
		                        "     "
		                        "     ", 25) == 0);

    CHECK_CMP (snake_start (s1, 2, 3, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s1), "     "
		                        "     "
		                        "     "
		                        "  @  "
		                        "     ", 25) == 0);
    CHECK (memcmp(snake_get_field (s2), "     "
		                        "  @# "
		                        "   + "
		                        "     "
		                        "     ", 25) == 0);
    snake_change_direction (s2, SNAKE_UP);
    CHECK_CMP (snake_step (s2),==,SNAKE_OKAY);
    snake_change_direction (s2, SNAKE_LEFT);
    CHECK_CMP (snake_step (s2),==,SNAKE_OKAY);
    CHECK_CMP (snake_step (s2),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s1), "     "
		                        "     "
		                        "     "
		                        "  @  "
		                        "     ", 25) == 0);
    CHECK (memcmp(snake_get_field (s2), "@##  "
		                        "  ## "
		                        "   + "
		                        "     "
		                        "     ", 25) == 0);

    CHECK_CMP (snake_start (s2, 3, 2, SNAKE_RIGHT),==,SNAKE_OKAY);
    CHECK (memcmp(snake_get_field (s1), "     "
		                        "     "
		                        "     "
		                        "  @  "
		                        "     ", 25) == 0);
    CHECK (memcmp(snake_get_field (s2), "     "
		                        "     "
		                        "   @ "
		                        "     "
		                        "     ", 25) == 0);
    snake_destroy (s1);
    snake_destroy (s2);
    TEST_PASSED;
}

TEST (spiral_5_by_5) {
    const int r = 5;
    const int c = 5;
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
    CHECK (memcmp(snake_get_field (s), "+####"
		                       "#####"
		                       "##@##"
		                       "#####"
		                       "#####", 25) == 0);
    snake_destroy (s);
    TEST_PASSED;
}

TEST (spiral) {
    const int r = 1001;
    const int c = 1001;
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
    const char * p = snake_get_field (s);
    CHECK_CMP (p[0],==,'+');
    for (int i = 1; i < r*c; ++i) {
	if (i == (c*(r/2) + c/2))
	    CHECK_CMP (p[i],==,'@');
	else
	    CHECK_CMP (p[i],==,'#');
    }	
    snake_destroy (s);
    TEST_PASSED;
}

MAIN_TEST_DRIVER ();
