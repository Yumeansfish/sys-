#include <stdio.h>

#include "basic_testing.h"

#include "../four.h"

TEST (empty) {
    struct game * g = create (5, 5, PLAYER_X);
    CHECK_INT_CMP (outcome(g),==,0);
    destroy(g);
    TEST_PASSED;
}

TEST (full_no_match) {
    struct game * g = create (5, 5, PLAYER_X);
    for (int i = 0; i < 25; ++i)
	move (g, 2*i % 5);
    CHECK_INT_CMP (outcome(g),==,0);
    destroy(g);
    TEST_PASSED;
}

TEST (simple_horizontal_x) {
    struct game * g = create (5, 5, PLAYER_X);
    move (g, 1);
    move (g, 1);
    move (g, 2);
    move (g, 2);
    move (g, 3);
    move (g, 3);
    move (g, 4);
    CHECK_INT_CMP (outcome(g),==,PLAYER_X);
    destroy(g);
    TEST_PASSED;
}

TEST (simple_horizontal_o) {
    struct game * g = create (5, 5, PLAYER_O);
    move (g, 1);
    move (g, 1);
    move (g, 2);
    move (g, 2);
    move (g, 3);
    move (g, 3);
    move (g, 4);
    CHECK_INT_CMP (outcome(g),==,PLAYER_O);
    destroy(g);
    TEST_PASSED;
}

TEST (simple_vertical_x) {
    struct game * g = create (5, 5, PLAYER_X);
    move (g, 1);
    move (g, 2);
    move (g, 1);
    move (g, 2);
    move (g, 1);
    move (g, 2);
    move (g, 1);
    CHECK_INT_CMP (outcome(g),==,PLAYER_X);
    destroy(g);
    TEST_PASSED;
}

TEST (simple_vertical_o) {
    struct game * g = create (5, 5, PLAYER_O);
    move (g, 1);
    move (g, 2);
    move (g, 1);
    move (g, 2);
    move (g, 1);
    move (g, 2);
    move (g, 1);
    CHECK_INT_CMP (outcome(g),==,PLAYER_O);
    destroy(g);
    TEST_PASSED;
}

TEST (diagonal_up_x) {
    struct game * g = create (5, 5, PLAYER_X);
    move (g, 1);
    move (g, 2);
    move (g, 2);
    move (g, 4);
    move (g, 3);
    move (g, 3);
    move (g, 4);
    move (g, 4);
    move (g, 3);
    move (g, 0);
    move (g, 4);
    CHECK_INT_CMP (outcome(g),==,PLAYER_X);
    destroy(g);
    TEST_PASSED;
}

TEST (diagonal_down_o) {
    struct game * g = create (5, 5, PLAYER_O);
    move (g, 4);
    move (g, 3);
    move (g, 3);
    move (g, 1);
    move (g, 2);
    move (g, 2);
    move (g, 1);
    move (g, 1);
    move (g, 2);
    move (g, 0);
    move (g, 1);
    CHECK_INT_CMP (outcome(g),==,PLAYER_O);
    destroy(g);
    TEST_PASSED;
}

TEST (diagonal_up_one_x) {
    struct game * g = create (5, 5, PLAYER_X);
    move (g, 1);
    move (g, 2);
    move (g, 3);
    move (g, 4);
    move (g, 1);
    move (g, 2);
    move (g, 3);
    move (g, 4);
    move (g, 2);
    move (g, 2);
    move (g, 4);
    move (g, 3);
    move (g, 3);
    move (g, 4);
    move (g, 1);
    move (g, 0);
    move (g, 0);
    move (g, 0);
    move (g, 0);
    move (g, 1);
    CHECK_INT_CMP (outcome(g),==,0);
    move (g, 4);
    CHECK_INT_CMP (outcome(g),==,PLAYER_X);
    destroy (g);
    TEST_PASSED;
}

TEST (diagonal_down_one_o) {
    struct game * g = create (5, 5, PLAYER_X);
    move (g, 1);
    move (g, 2);
    move (g, 3);
    move (g, 4);
    move (g, 1);
    move (g, 2);
    move (g, 3);
    move (g, 4);
    move (g, 2);
    move (g, 2);
    move (g, 4);
    move (g, 3);
    move (g, 3);
    move (g, 4);
    move (g, 1);
    move (g, 0);
    move (g, 0);
    move (g, 0);
    move (g, 0);
    move (g, 1);
    CHECK_INT_CMP (outcome(g),==,0);
    move (g, 0);
    move (g, 1);
    CHECK_INT_CMP (outcome(g),==,PLAYER_O);
    destroy (g);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(empty,
		 full_no_match,
		 simple_horizontal_x,
		 simple_horizontal_o,
		 simple_vertical_x,
		 simple_vertical_o,
		 diagonal_up_x,
		 diagonal_down_o,
		 diagonal_up_one_x,
		 diagonal_down_one_o);
		 
