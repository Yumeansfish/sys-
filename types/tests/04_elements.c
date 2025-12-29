#include <stdlib.h> 		/* for NULL */

#include "basic_testing.h"

#include "../types.h"

TEST (add_one_then_another_element) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (types_count(ts) == 1);
    CHECK (elements_count(ts, "A") == 0);
    CHECK (elements_subtype_count(ts, "A") == 0);
    CHECK (add_element(ts, "A") == TS_SUCCESS);
    CHECK (types_count(ts) == 1);
    CHECK (elements_count(ts, "A") == 1);
    CHECK (elements_subtype_count(ts, "A") == 0);
    CHECK (add_element(ts, "A") == TS_SUCCESS);
    CHECK (types_count(ts) == 1);
    CHECK (elements_count(ts, "A") == 2);
    CHECK (elements_subtype_count(ts, "A") == 0);
    destroy(ts);
}

TEST (b_is_a_add_one_element_each) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "B", "A") == TS_SUCCESS);
    CHECK (add_element(ts, "A") == TS_SUCCESS);
    CHECK (types_count(ts) == 2);
    CHECK (elements_count(ts, "A") == 1);
    CHECK (elements_count(ts, "B") == 0);
    fprintf(stderr, "%d\n", elements_subtype_count(ts, "A"));
    CHECK (elements_subtype_count(ts, "A") == 0);
    CHECK (add_element(ts, "B") == TS_SUCCESS);
    CHECK (types_count(ts) == 2);
    CHECK (elements_count(ts, "A") == 1);
    CHECK (elements_count(ts, "B") == 1);
    CHECK (elements_subtype_count(ts, "A") == 1);
    destroy(ts);
}

TEST (deep_hierarcy) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "A.A", "A") == TS_SUCCESS);
    CHECK (add_type(ts, "A.A.B", "A.A") == TS_SUCCESS);
    CHECK (add_type(ts, "A.A.C", "A.A") == TS_SUCCESS);
    CHECK (add_type(ts, "A.A.C.C", "A.A.C") == TS_SUCCESS);
    CHECK (add_type(ts, "X", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "X.Y", "X") == TS_SUCCESS);
    for (int i = 0; i < 10; ++i)
	CHECK (add_element(ts, "A.A.B") == TS_SUCCESS);
    for (int i = 0; i < 20; ++i)
	CHECK (add_element(ts, "A.A.C.C") == TS_SUCCESS);
    for (int i = 0; i < 50; ++i)
	CHECK (add_element(ts, "X.Y") == TS_SUCCESS);
    CHECK (elements_count(ts, "A") == 0);
    CHECK (elements_count(ts, "A.A") == 0);
    CHECK (elements_count(ts, "A.A.B") == 10);
    CHECK (elements_count(ts, "A.A.C") == 0);
    CHECK (elements_count(ts, "A.A.C.C") == 20);
    CHECK (elements_count(ts, "X") == 0);
    CHECK (elements_count(ts, "X.Y") == 50);
    fprintf(stderr,"%d\n",elements_subtype_count(ts,"A"));
    CHECK (elements_subtype_count(ts, "A") == 30);
    CHECK (elements_subtype_count(ts, "A.A") == 30);
    CHECK (elements_subtype_count(ts, "A.A.B") == 0);
    CHECK (elements_subtype_count(ts, "A.A.C") == 20);
    CHECK (elements_subtype_count(ts, "A.A.C.C") == 0);
    CHECK (elements_subtype_count(ts, "X") == 50);
    CHECK (elements_subtype_count(ts, "X.Y") == 0);
    destroy(ts);
}

MAIN_TEST_DRIVER(add_one_then_another_element,
		 b_is_a_add_one_element_each,
		 deep_hierarcy);
