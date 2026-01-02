#include <stdio.h>

#include "basic_testing.h"

#include "../four.h"

TEST (empty_small) {
    struct game * g = create (5, 5, PLAYER_X);
    for (int c = 0; c < 5; ++c)
	for (int r = 0; r < 5; ++r)
	    CHECK_INT_CMP (get_cell(g,c,r),==,EMPTY);
    destroy(g);
    TEST_PASSED;
}

TEST (empty_large) {
    struct game * g = create (901, 700, PLAYER_X);
    for (int c = 0; c < 901; ++c)
	for (int r = 0; r < 700; ++r)
	    CHECK_INT_CMP (get_cell(g,c,r),==,EMPTY);
    destroy(g);
    TEST_PASSED;
}

TEST (one_small_x) {
    struct game * g = create (5, 5, PLAYER_X);
    move (g, 2);
    for (int c = 0; c < 5; ++c)
	for (int r = 0; r < 5; ++r)
	    if (c == 2 && r == 0)
		CHECK_INT_CMP (get_cell(g,c,r),==,PLAYER_X);
	    else
		CHECK_INT_CMP (get_cell(g,c,r),==,EMPTY);
    destroy(g);
    TEST_PASSED;
}

TEST (one_large_x) {
    struct game * g = create (901, 700, PLAYER_X);
    move (g, 237);
    for (int c = 0; c < 901; ++c)
	for (int r = 0; r < 700; ++r)
	    if (c == 237 && r == 0)
		CHECK_INT_CMP (get_cell(g,c,r),==,PLAYER_X);
	    else
		CHECK_INT_CMP (get_cell(g,c,r),==,EMPTY);
    destroy(g);
    TEST_PASSED;
}

TEST (two_large_xo) {
    struct game * g1 = create (901, 700, PLAYER_X);
    struct game * g2 = create (701, 500, PLAYER_O);
    move (g1, 237);
    move (g2, 238);
    for (int c = 0; c < 901; ++c)
	for (int r = 0; r < 700; ++r)
	    if (c == 237 && r == 0)
		CHECK_INT_CMP (get_cell(g1,c,r),==,PLAYER_X);
	    else
		CHECK_INT_CMP (get_cell(g1,c,r),==,EMPTY);
    for (int c = 0; c < 701; ++c)
	for (int r = 0; r < 500; ++r)
	    if (c == 238 && r == 0)
		CHECK_INT_CMP (get_cell(g2,c,r),==,PLAYER_O);
	    else
		CHECK_INT_CMP (get_cell(g2,c,r),==,EMPTY);
    destroy(g2);
    destroy(g1);
    TEST_PASSED;
}

TEST (multi_small_x) {
    struct game * g = create (7, 11, PLAYER_X);
    move (g, 3);
    move (g, 5);
    move (g, 4);
    move (g, 5);
    move (g, 3);
    move (g, 3);
    move (g, 4);

    CHECK_INT_CMP (get_cell(g,3,0),==,PLAYER_X);
    CHECK_INT_CMP (get_cell(g,4,0),==,PLAYER_X);
    CHECK_INT_CMP (get_cell(g,3,1),==,PLAYER_X);
    CHECK_INT_CMP (get_cell(g,4,1),==,PLAYER_X);

    CHECK_INT_CMP (get_cell(g,3,2),==,PLAYER_O);
    CHECK_INT_CMP (get_cell(g,5,0),==,PLAYER_O);
    CHECK_INT_CMP (get_cell(g,5,1),==,PLAYER_O);

    destroy(g);
    TEST_PASSED;
}

TEST (multi_small_o) {
    struct game * g = create (7, 11, PLAYER_O);
    move (g, 3);
    move (g, 5);
    move (g, 4);
    move (g, 5);
    move (g, 3);
    move (g, 3);
    move (g, 4);

    CHECK_INT_CMP (get_cell(g,3,0),==,PLAYER_O);
    CHECK_INT_CMP (get_cell(g,4,0),==,PLAYER_O);
    CHECK_INT_CMP (get_cell(g,3,1),==,PLAYER_O);
    CHECK_INT_CMP (get_cell(g,4,1),==,PLAYER_O);

    CHECK_INT_CMP (get_cell(g,3,2),==,PLAYER_X);
    CHECK_INT_CMP (get_cell(g,5,0),==,PLAYER_X);
    CHECK_INT_CMP (get_cell(g,5,1),==,PLAYER_X);

    destroy(g);
    TEST_PASSED;
}

TEST (corners) {
    struct game * g = create (7, 3, PLAYER_O);
    move (g, 0);		/* O */
    move (g, 0);		/* X */
    move (g, 4);		/* O */
    move (g, 6);		/* X */
    move (g, 6);		/* O */
    move (g, 3);		/* X */
    move (g, 6);		/* O */
    move (g, 0);		/* X */

    CHECK_INT_CMP (get_cell(g,0,0),==,PLAYER_O);
    CHECK_INT_CMP (get_cell(g,0,2),==,PLAYER_X);
    CHECK_INT_CMP (get_cell(g,6,0),==,PLAYER_X);
    CHECK_INT_CMP (get_cell(g,6,2),==,PLAYER_O);

    destroy(g);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(empty_small,
		 empty_large,
		 one_small_x,
		 two_large_xo,
		 multi_small_x,
		 multi_small_o,
		 corners);
