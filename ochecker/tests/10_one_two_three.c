#include "basic_testing.h"
#include "../ochecker.h"

TEST (create_open_destroy) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/one_two_three"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (single_string_output) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/one_two_three"));
    CHECK (oc_puts(oc, "one\ntwo\nthree\n"));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (create_open_destroy,
		  single_string_output);
