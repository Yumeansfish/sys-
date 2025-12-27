#include "basic_testing.h"
#include "../ochecker.h"

TEST (status_on_empty_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_status(oc) == OC_CLOSED);
    CHECK (oc_open_file(oc, "tests/empty_file"));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (oc_close(oc));
    CHECK (oc_status(oc) == OC_CLOSED);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (status_on_empty_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_status(oc) == OC_CLOSED);
    CHECK (oc_open_str(oc, ""));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (oc_close(oc));
    CHECK (oc_status(oc) == OC_CLOSED);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (status_on_empty_memory) {
    struct ochecker * oc = oc_create();
    char c;
    CHECK (oc_status(oc) == OC_CLOSED);
    CHECK (oc_open_mem(oc, &c, &c));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (oc_close(oc));
    CHECK (oc_status(oc) == OC_CLOSED);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (status_on_one_two_three_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/one_two_three"));
    CHECK (oc_puts(oc, "one"));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (oc_puts(oc, "\nt"));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (oc_puts(oc, "wo\n"));
    CHECK (oc_status(oc) == OC_OPEN);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (status_on_one_two_three_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "one\ntwo\nthree\n"));
    CHECK (oc_puts(oc, "one"));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (oc_puts(oc, "\nt"));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (oc_puts(oc, "wo\n"));
    CHECK (oc_status(oc) == OC_OPEN);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (status_on_one_two_three_memory) {
    struct ochecker * oc = oc_create();
    const char * buf = "one\ntwo\nthree\n";
    CHECK (oc_open_mem(oc, buf, buf + 14));
    CHECK (oc_puts(oc, "one"));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (oc_puts(oc, "\nt"));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (oc_puts(oc, "wo\n"));
    CHECK (oc_status(oc) == OC_OPEN);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (status_on_one_two_three_error_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/one_two_three"));
    CHECK (oc_puts(oc, "one"));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (!oc_puts(oc, "\nX"));
    CHECK (oc_status(oc) == OC_ERROR);
    CHECK (!oc_puts(oc, "wo\n"));
    CHECK (oc_status(oc) == OC_ERROR);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (status_on_one_two_three_error_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "one\ntwo\nthree\n"));
    CHECK (oc_puts(oc, "one"));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (!oc_puts(oc, "\nX"));
    CHECK (oc_status(oc) == OC_ERROR);
    CHECK (!oc_puts(oc, "wo\n"));
    CHECK (oc_status(oc) == OC_ERROR);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (status_on_one_two_three_error_memory) {
    struct ochecker * oc = oc_create();
    const char * buf = "one\ntwo\nthree\n";
    CHECK (oc_open_mem(oc, buf, buf + 14));
    CHECK (oc_puts(oc, "one"));
    CHECK (oc_status(oc) == OC_OPEN);
    CHECK (!oc_puts(oc, "\nX"));
    CHECK (oc_status(oc) == OC_ERROR);
    CHECK (!oc_puts(oc, "wo\n"));
    CHECK (oc_status(oc) == OC_ERROR);
    oc_destroy(oc);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (status_on_empty_file,
		  status_on_empty_str,
		  status_on_empty_memory,
		  status_on_one_two_three_file,
		  status_on_one_two_three_str,
		  status_on_one_two_three_memory,
		  status_on_one_two_three_error_file,
		  status_on_one_two_three_error_str,
		  status_on_one_two_three_error_memory);
