#include <stdio.h>

#include "basic_testing.h"

#include "../four.h"

TEST (empty_small) {
    struct game * g = create (5, 5, PLAYER_X);
    CHECK (!board_full (g));
    destroy(g);
    TEST_PASSED;
}

TEST (full_small) {
    struct game * g = create (5, 5, PLAYER_X);
    for (int i = 0; i < 25; ++i) 
	CHECK_INT_CMP(move(g,(2*i % 5)),==,1);
    CHECK (board_full (g));
    destroy(g);
    TEST_PASSED;
}


TEST (non_full_small) {
    struct game * g = create (5, 5, PLAYER_X);
    for (int i = 0; i < 24; ++i) 
	CHECK_INT_CMP(move(g,(2*i % 5)),==,1);
    CHECK (!board_full (g));
    destroy(g);
    TEST_PASSED;
}

TEST (empty_large) {
    struct game * g = create (900, 700, PLAYER_X);
    CHECK (!board_full (g));
    destroy(g);
    TEST_PASSED;
}

TEST (full_large) {
    struct game * g = create (901, 700, PLAYER_X);
    for (int i = 0; i < 901*700; ++i) {
	int res = move(g,(2*i % 901));
	CHECK_INT_CMP(res,==,1);
    }
    CHECK (board_full (g));
    destroy(g);
    TEST_PASSED;
}

TEST (non_full_large) {
    struct game * g = create (901, 901, PLAYER_X);
    for (int i = 0; i < 901*700 - 1; ++i) 
	CHECK_INT_CMP(move(g,(2*i % 901)),==,1);
    CHECK (!board_full (g));
    destroy(g);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(empty_small,
		 full_small,
		 non_full_small,
		 empty_large,
		 full_large,
		 non_full_large);
