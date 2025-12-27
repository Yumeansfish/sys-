#include "basic_testing.h"
#include "../ochecker.h"

TEST (positions_on_empty_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/empty_file"));
    CHECK_CMP (oc_position(oc),==,1);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,1);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (positions_on_empty_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, ""));
    CHECK_CMP (oc_position(oc),==,1);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,1);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (positions_on_empty_memory) {
    struct ochecker * oc = oc_create();
    char c;
    CHECK (oc_open_mem(oc, &c, &c));
    CHECK_CMP (oc_position(oc),==,1);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,1);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (positions_on_one_two_three_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/one_two_three"));
    CHECK_CMP (oc_position(oc),==,1);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,1);
    CHECK (oc_puts(oc, "one"));
    CHECK_CMP (oc_position(oc),==,4);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,4);
    CHECK (oc_puts(oc, "\nt"));
    CHECK_CMP (oc_position(oc),==,6);
    CHECK_CMP (oc_line(oc),==,2);
    CHECK_CMP (oc_column(oc),==,2);
    CHECK (oc_puts(oc, "wo\n"));
    CHECK_CMP (oc_position(oc),==,9);
    CHECK_CMP (oc_line(oc),==,3);
    CHECK_CMP (oc_column(oc),==,1);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (positions_on_one_two_three_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "one\ntwo\nthree\n"));
    CHECK_CMP (oc_position(oc),==,1);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,1);
    CHECK (oc_puts(oc, "one"));
    CHECK_CMP (oc_position(oc),==,4);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,4);
    CHECK (oc_puts(oc, "\nt"));
    CHECK_CMP (oc_position(oc),==,6);
    CHECK_CMP (oc_line(oc),==,2);
    CHECK_CMP (oc_column(oc),==,2);
    CHECK (oc_puts(oc, "wo\n"));
    CHECK_CMP (oc_position(oc),==,9);
    CHECK_CMP (oc_line(oc),==,3);
    CHECK_CMP (oc_column(oc),==,1);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (positions_on_one_two_three_memory) {
    struct ochecker * oc = oc_create();
    const char * buf = "one\ntwo\nthree\n";
    CHECK (oc_open_mem(oc, buf, buf + 14));
    CHECK_CMP (oc_position(oc),==,1);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,1);
    CHECK (oc_puts(oc, "one"));
    CHECK_CMP (oc_position(oc),==,4);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,4);
    CHECK (oc_puts(oc, "\nt"));
    CHECK_CMP (oc_position(oc),==,6);
    CHECK_CMP (oc_line(oc),==,2);
    CHECK_CMP (oc_column(oc),==,2);
    CHECK (oc_puts(oc, "wo\n"));
    CHECK_CMP (oc_position(oc),==,9);
    CHECK_CMP (oc_line(oc),==,3);
    CHECK_CMP (oc_column(oc),==,1);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (positions_on_one_two_three_error_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/one_two_three"));
    CHECK_CMP (oc_position(oc),==,1);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,1);
    CHECK (oc_puts(oc, "one"));
    CHECK_CMP (oc_position(oc),==,4);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,4);
    CHECK (!oc_puts(oc, "\nX"));
    CHECK_CMP (oc_position(oc),==,5);
    CHECK_CMP (oc_line(oc),==,2);
    CHECK_CMP (oc_column(oc),==,1);
    CHECK (!oc_puts(oc, "wo\n"));
    CHECK_CMP (oc_position(oc),==,5);
    CHECK_CMP (oc_line(oc),==,2);
    CHECK_CMP (oc_column(oc),==,1);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (positions_on_one_two_three_error_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "one\ntwo\nthree\n"));
    CHECK_CMP (oc_position(oc),==,1);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,1);
    CHECK (oc_puts(oc, "one"));
    CHECK_CMP (oc_position(oc),==,4);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,4);
    CHECK (!oc_puts(oc, "\nX"));
    CHECK_CMP (oc_position(oc),==,5);
    CHECK_CMP (oc_line(oc),==,2);
    CHECK_CMP (oc_column(oc),==,1);
    CHECK (!oc_puts(oc, "wo\n"));
    CHECK_CMP (oc_position(oc),==,5);
    CHECK_CMP (oc_line(oc),==,2);
    CHECK_CMP (oc_column(oc),==,1);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (positions_on_one_two_three_error_memory) {
    struct ochecker * oc = oc_create();
    const char * buf = "one\ntwo\nthree\n";
    CHECK (oc_open_mem(oc, buf, buf + 14));
    CHECK_CMP (oc_position(oc),==,1);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,1);
    CHECK (oc_puts(oc, "one"));
    CHECK_CMP (oc_position(oc),==,4);
    CHECK_CMP (oc_line(oc),==,1);
    CHECK_CMP (oc_column(oc),==,4);
    CHECK (!oc_puts(oc, "\nX"));
    CHECK_CMP (oc_position(oc),==,5);
    CHECK_CMP (oc_line(oc),==,2);
    CHECK_CMP (oc_column(oc),==,1);
    CHECK (!oc_puts(oc, "wo\n"));
    CHECK_CMP (oc_position(oc),==,5);
    CHECK_CMP (oc_line(oc),==,2);
    CHECK_CMP (oc_column(oc),==,1);
    oc_destroy(oc);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (positions_on_empty_file,
		  positions_on_empty_str,
		  positions_on_empty_memory,
		  positions_on_one_two_three_file,
		  positions_on_one_two_three_str,
		  positions_on_one_two_three_memory,
		  positions_on_one_two_three_error_file,
		  positions_on_one_two_three_error_str,
		  positions_on_one_two_three_error_memory);
