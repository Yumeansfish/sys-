#include <stdlib.h> 		/* for NULL */

#include "basic_testing.h"

#include "../types.h"

TEST (create_empty) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    /* a newly created type system must be empty */
    CHECK (types_count(ts) == 0); 
    destroy(ts);
}

TEST (create_add_one) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    destroy(ts);
}

TEST (create_add_a_bunch) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "B", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "AB", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "BA", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "AA", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "BB", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "There are two types of people:"
			" those who can extrapolate"
			" from incomplete data", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "AB", NULL) == TS_TYPE_EXISTS);
    char name[1000];
    strcpy(name, "There are two types of people:"
		 " those who can extrapolate"
		 " from incomplete data");
    CHECK (add_type(ts, name, NULL) == TS_TYPE_EXISTS);
    strcpy(name, "There are two types of people:"
		 " those who can extrapolate"
		 " from incomplete data.");
    CHECK (add_type(ts, name, NULL) == TS_SUCCESS);
    destroy(ts);
}

TEST (create_add_invalid_name) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    const char * typename = 	/* 256 A's */
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    /* 256 characters is the limit, so this is okay. */
    CHECK (add_type(ts, typename, NULL) == TS_SUCCESS);
    typename = 	/* 257 B's */
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
    /* 256 characters is over the limit, so this is not okay. */
    CHECK (add_type(ts, typename, NULL) == TS_BAD_TYPENAME);
    /* The name can not be an empty string. */
    CHECK (add_type(ts, "", NULL) == TS_BAD_TYPENAME);
    destroy(ts);
}

TEST (create_add_with_reused_name_buffer) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    char name[2];
    name[0] = 'A'; name[1] = 0; /* name <-- "A" */
    CHECK (add_type(ts, name, NULL) == TS_SUCCESS);
    name[0] = 'B'; name[1] = 0; /* name <-- "B" */
    CHECK (add_type(ts, name, NULL) == TS_SUCCESS);
    /* The name buffer belongs to the caller.  You must _copy_ names
       within your data structure. */
    destroy(ts);
}

TEST (create_add_with_same_name_error) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "A", NULL) == TS_TYPE_EXISTS);
    destroy(ts);
}

TEST (create_add_with_supertype_name) {
    struct type_system * ts = create();
    CHECK (ts != NULL);
    CHECK (add_type(ts, "A", NULL) == TS_SUCCESS);
    CHECK (add_type(ts, "B", "A") == TS_SUCCESS);
    destroy(ts);
}

MAIN_TEST_DRIVER(create_empty,
		 create_add_one,
		 create_add_a_bunch,
		 create_add_invalid_name,
		 create_add_with_reused_name_buffer,
		 create_add_with_same_name_error,
		 create_add_with_supertype_name);
