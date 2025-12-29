#include <stdlib.h> 		/* for NULL */

#include "basic_testing.h"

#include "../types.h"

TEST (create_two) {
    struct type_system * ts1 = create();
    CHECK (ts1 != NULL);
    struct type_system * ts2 = create();
    CHECK (ts2 != NULL);
    CHECK (ts1 != ts2);
    destroy(ts1);
    destroy(ts2);
}

TEST (create_two_add_two) {
    struct type_system * ts1 = create();
    CHECK (ts1 != NULL);
    struct type_system * ts2 = create();
    CHECK (ts2 != NULL);
    CHECK (add_type(ts1, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts1, "B", NULL) == TS_SUCCESS);
    CHECK (types_count(ts2) == 0);
    CHECK (add_type(ts2, "A", NULL) == TS_SUCCESS);
    CHECK (types_count(ts1) == 2);
    CHECK (types_count(ts2) == 1);
    destroy(ts1);
    CHECK (add_type(ts2, "B", NULL) == TS_SUCCESS);
    destroy(ts2);
}

MAIN_TEST_DRIVER(create_two,
		 create_two_add_two);
