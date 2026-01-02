#include <stdio.h>

#include "basic_testing.h"

#include "../four.h"

TEST (create_destroy_small) {
    struct game * g = create (5, 5, PLAYER_X);
    CHECK (g != 0);
    destroy(g);
    TEST_PASSED;
}

TEST (create_destroy_two) {
    struct game * g1 = create (15, 25, PLAYER_X);
    CHECK (g1 != 0);
    struct game * g2 = create (25, 35, PLAYER_O);
    CHECK (g2 != 0);
    destroy(g1);
    destroy(g2);
    TEST_PASSED;
}

TEST (create_destroy_two_large) {
    struct game * g1 = create (700, 900, PLAYER_X);
    CHECK (g1 != 0);
    struct game * g2 = create (1000, 1000, PLAYER_O);
    CHECK (g2 != 0);
    destroy(g1);
    destroy(g2);
    TEST_PASSED;
}

TEST (get_dimentions_small) {
    struct game * g = create (5, 5, PLAYER_X);
    CHECK_INT_CMP (get_columns (g),==,5);
    CHECK_INT_CMP (get_rows (g),==,5);
    destroy(g);
    TEST_PASSED;
}

TEST (get_dimentions_two) {
    struct game * g1 = create (5, 5, PLAYER_X);
    struct game * g2 = create (7, 11, PLAYER_X);
    CHECK_INT_CMP (get_columns (g2),==,7);
    CHECK_INT_CMP (get_rows (g2),==,11);
    CHECK_INT_CMP (get_columns (g1),==,5);
    CHECK_INT_CMP (get_rows (g1),==,5);
    destroy(g1);
    destroy(g2);
    TEST_PASSED;
}

TEST (get_player_x) {
    struct game * g = create (7, 11, PLAYER_X);
    CHECK_INT_CMP (get_next_player (g),==,PLAYER_X);
    CHECK_INT_CMP (get_next_player (g),==,PLAYER_X);
    destroy(g);
    TEST_PASSED;
}

TEST (get_player_o) {
    struct game * g = create (7, 11, PLAYER_O);
    CHECK_INT_CMP (get_next_player (g),==,PLAYER_O);
    CHECK_INT_CMP (get_next_player (g),==,PLAYER_O);
    destroy(g);
    TEST_PASSED;
}

TEST (get_player_two) {
    struct game * g1 = create (5, 5, PLAYER_O);
    struct game * g2 = create (7, 11, PLAYER_X);
    CHECK_INT_CMP (get_next_player (g2),==,PLAYER_X);
    CHECK_INT_CMP (get_next_player (g1),==,PLAYER_O);
    destroy(g1);
    destroy(g2);
    TEST_PASSED;
}

TEST (restart_simple) {
    struct game * g = create (5, 5, PLAYER_X);
    CHECK (g != 0);
    move (g, 0);
    CHECK_INT_CMP(get_cell(g, 0, 0), ==, PLAYER_X);
    restart (g, PLAYER_O);
    CHECK_INT_CMP(get_cell(g, 0, 0), ==, EMPTY);
    move (g, 0);
    CHECK_INT_CMP(get_cell(g, 0, 0), ==, PLAYER_O);
    destroy(g);
    TEST_PASSED;
}

TEST (restart_line) {
    struct game * g = create (5, 5, PLAYER_X);
    CHECK (g != 0);
    for (int i = 0; i < 5; ++i)
	move (g, i);
    for (int i = 0; i < 5; ++i) {
	CHECK_INT_CMP(get_cell(g, i, 0), !=, EMPTY);
	CHECK_INT_CMP(get_cell(g, i, 1), ==, EMPTY);
    }
    for (int i = 0; i < 5; ++i)
	move (g, i);
    for (int i = 0; i < 5; ++i) {
	CHECK_INT_CMP(get_cell(g, i, 0), !=, EMPTY);
	CHECK_INT_CMP(get_cell(g, i, 1), !=, EMPTY);
    }
    restart (g, PLAYER_O);
    for (int i = 0; i < 5; ++i) 
	for (int j = 0; j < 5; ++j) 
	    CHECK_INT_CMP(get_cell(g, i, j), ==, EMPTY);

    for (int i = 0; i < 5; ++i)
	move (g, i);
    for (int i = 0; i < 5; ++i) {
	CHECK_INT_CMP(get_cell(g, i, 0), !=, EMPTY);
	CHECK_INT_CMP(get_cell(g, i, 1), ==, EMPTY);
    }
    destroy(g);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(create_destroy_small,
		 create_destroy_two,
		 create_destroy_two_large,
		 get_dimentions_small,
		 get_dimentions_two,
		 get_player_x,
		 get_player_o,
		 get_player_two,
		 restart_simple,
		 restart_line);
