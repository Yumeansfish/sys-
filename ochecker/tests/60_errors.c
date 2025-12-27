#include "basic_testing.h"
#include "../ochecker.h"
#include <string.h>

TEST (open_not_existing_file) {
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (!oc_open_file(oc, "tests/not_existing_file"));
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_on_closed_checker) {
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (!oc_putc(oc, 'c'));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_on_closed_checker) {
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (!oc_puts(oc, "test_puts"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_on_closed_checker) {
    char buf[] = "test_write";
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (!oc_write(oc, buf, strlen(buf)));
    oc_destroy (oc);
    TEST_PASSED;
}

TEST (putc_on_errored_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (!oc_putc(oc, 'c'));
    CHECK (!oc_putc(oc, 'a'));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_on_errored_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (!oc_putc(oc, 'c'));
    CHECK (!oc_putc(oc, 'a'));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_on_errored_mem) {
    char buf[] = "abc";
    struct ochecker * oc = oc_create();
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (!oc_putc(oc, 'c'));
    CHECK (!oc_putc(oc, 'a'));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_on_errored_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (!oc_puts(oc, "cba"));
    CHECK (!oc_puts(oc, "abc"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_on_errored_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (!oc_puts(oc, "bca"));
    CHECK (!oc_puts(oc, "abc"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_on_errored_mem) {
    char buf[] = "abc";
    struct ochecker * oc = oc_create();
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (!oc_puts(oc, "bca"));
    CHECK (!oc_puts(oc, "abc"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_on_errored_file) {
    char abc_buf[] = "abc";
    char bca_buf[] = "bca";
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (!oc_write(oc, bca_buf, strlen(bca_buf)));
    CHECK (!oc_write(oc, abc_buf, strlen(abc_buf)));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_on_errored_str) {
    char abc_buf[] = "abc";
    char bca_buf[] = "bca";
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (!oc_write(oc, bca_buf, strlen(bca_buf)));
    CHECK (!oc_write(oc, abc_buf, strlen(abc_buf)));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_on_errored_mem) {
    char buf[] = "abc";
    char bca_buf[] = "bca";
    struct ochecker * oc = oc_create();
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (!oc_write(oc, bca_buf, strlen(bca_buf)));
    CHECK (!oc_write(oc, buf, strlen(buf)));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (close_before_eof_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (oc_putc(oc, 'a'));
    CHECK (!oc_close(oc));
    CHECK_CMP (oc_status(oc),==,OC_ERROR);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (close_before_eof_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (oc_putc(oc, 'a'));
    CHECK (!oc_close(oc));
    CHECK_CMP (oc_status(oc),==,OC_ERROR);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (close_before_eof_mem) {
    char buf[] = "abc";
    struct ochecker * oc = oc_create();
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (oc_putc(oc, 'a'));
    CHECK (!oc_close(oc));
    CHECK_CMP (oc_status(oc),==,OC_ERROR);
    oc_destroy(oc);
    TEST_PASSED;
}


MAIN_TEST_DRIVER (open_not_existing_file,
		  putc_on_closed_checker,
		  puts_on_closed_checker,
		  write_on_closed_checker,
		  putc_on_errored_file,
		  putc_on_errored_str,
		  putc_on_errored_mem,
		  puts_on_errored_file,
		  puts_on_errored_str,
		  puts_on_errored_mem,
		  write_on_errored_file,
		  write_on_errored_str,
		  write_on_errored_mem,
		  close_before_eof_file,
		  close_before_eof_str,
		  close_before_eof_mem);
