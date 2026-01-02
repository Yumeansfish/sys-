#include <stdio.h>

#include "basic_testing.h"

#include "../four.h"

TEST (fill_five_by_five) {
    struct game * g = create (5, 5, PLAYER_X);
    for (int i = 0; i < 5*5; ++i) {
	CHECK_INT_CMP (move(g,(2*i%5)),==,1);
    }
    for (int i = 0; i < 5; ++i)
	CHECK_INT_CMP (move(g,i),==,0);
    destroy(g);
    TEST_PASSED;
}

TEST (full_columns) {
    struct game * g = create (7, 3, PLAYER_X);
    CHECK_INT_CMP (move(g,0),==,1);
    CHECK_INT_CMP (move(g,0),==,1);
    CHECK_INT_CMP (move(g,0),==,1);
    CHECK_INT_CMP (move(g,0),==,0);

    CHECK_INT_CMP (move(g,5),==,1);
    CHECK_INT_CMP (move(g,5),==,1);
    CHECK_INT_CMP (move(g,5),==,1);
    CHECK_INT_CMP (move(g,5),==,0);

    destroy(g);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(fill_five_by_five, full_columns);
