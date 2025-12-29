#include <stdlib.h> 		/* for NULL */

#include "basic_testing.h"

#include "../types.h"

TEST (b_is_a) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "B", "A") == TS_SUCCESS);
    CHECK (is_subtype (ts, "B", "A") == TS_TRUE);
    CHECK (is_subtype (ts, "A", "B") == TS_FALSE);
    destroy(ts);
}

TEST (b_is_not_a) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "B", NULL) == TS_SUCCESS);
    CHECK (is_subtype (ts, "B", "A") == TS_FALSE);
    CHECK (is_subtype (ts, "A", "B") == TS_FALSE);
    destroy(ts);
}

TEST (c_is_b_is_a) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "B", "A") == TS_SUCCESS);
    CHECK (add_type(ts, "C", "B") == TS_SUCCESS);
    CHECK (is_subtype (ts, "C", "B") == TS_TRUE);
    CHECK (is_subtype (ts, "B", "A") == TS_TRUE);
    CHECK (is_subtype (ts, "C", "A") == TS_TRUE);
    destroy(ts);
}

TEST (c_and_b_are_a) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "B", "A") == TS_SUCCESS);
    CHECK (add_type(ts, "C", "A") == TS_SUCCESS);
    CHECK (is_subtype (ts, "B", "C") == TS_FALSE);
    CHECK (is_subtype (ts, "C", "B") == TS_FALSE);
    CHECK (is_subtype (ts, "B", "A") == TS_TRUE);
    CHECK (is_subtype (ts, "C", "A") == TS_TRUE);
    destroy(ts);
}

TEST (is_subtype_errors) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "B", "A") == TS_SUCCESS);
    CHECK (is_subtype (ts, "C", "B") == TS_UNKNOWN_TYPE);
    CHECK (is_subtype (ts, "B", "C") == TS_UNKNOWN_SUPERTYPE);
    CHECK (add_type(ts, "C", "A") == TS_SUCCESS);
    CHECK (is_subtype (ts, "B", "C") == TS_FALSE);
    CHECK (is_subtype (ts, "C", "B") == TS_FALSE);
    CHECK (is_subtype (ts, "B", "A") == TS_TRUE);
    CHECK (is_subtype (ts, "C", "A") == TS_TRUE);
    destroy(ts);
}

TEST (subtype_and_count) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (types_count(ts) == 1);
    CHECK (add_type(ts, "B", "A") == TS_SUCCESS);
    CHECK (types_count(ts) == 2);
    CHECK (add_type(ts, "C", "A") == TS_SUCCESS);
    CHECK (types_count(ts) == 3);
    destroy(ts);
}

MAIN_TEST_DRIVER(b_is_a,
		 b_is_not_a,
		 c_is_b_is_a,
		 c_and_b_are_a,
		 is_subtype_errors,
		 subtype_and_count);
