#include "basic_testing.h"
#include "../ochecker.h"
#include <string.h>

static const char * abc_str = "abc";
static const char * one_two_three_str = "one\ntwo\nthree\n";

TEST (reopen_closed_file) {
    char buf[] = "three\n";
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_puts(oc, "abc"));
    CHECK (oc_close(oc));
    CHECK (oc_open_file(oc, "tests/one_two_three"));
    CHECK (oc_putc(oc, 'o'));
    CHECK (oc_puts(oc, "ne\ntwo\n"));
    CHECK (oc_write(oc, buf, strlen(buf)));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (reopen_closed_str) {
    char buf[] = "three\n";
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (oc_open_str(oc, abc_str));
    CHECK (oc_puts(oc, abc_str));
    CHECK (oc_close(oc));
    CHECK (oc_open_str(oc, one_two_three_str));
    CHECK (oc_putc(oc, 'o'));
    CHECK (oc_puts(oc, "ne\ntwo\n"));
    CHECK (oc_write(oc, buf, strlen(buf)));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (reopen_closed_mem) {
    char buf[] = "three\n";
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (oc_open_mem(oc, abc_str, abc_str + strlen(abc_str)));
    CHECK (oc_puts(oc, abc_str));
    CHECK (oc_close(oc));
    CHECK (oc_open_mem(oc, one_two_three_str, one_two_three_str + strlen(one_two_three_str)));
    CHECK (oc_putc(oc, 'o'));
    CHECK (oc_puts(oc, "ne\ntwo\n"));
    CHECK (oc_write(oc, buf, strlen(buf)));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (reopen_open_file) {
    char buf[] = "three\n";
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_putc(oc, 'a'));
    CHECK (oc_open_file(oc, "tests/one_two_three"));
    CHECK (oc_putc(oc, 'o'));
    CHECK (oc_puts(oc, "ne\ntwo\n"));
    CHECK (oc_write(oc, buf, strlen(buf)));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (reopen_open_str) {
    char buf[] = "three\n";
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (oc_open_str(oc, abc_str));
    CHECK (oc_putc(oc, 'a'));
    CHECK (oc_open_str(oc, one_two_three_str));
    CHECK (oc_putc(oc, 'o'));
    CHECK (oc_puts(oc, "ne\ntwo\n"));
    CHECK (oc_write(oc, buf, strlen(buf)));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (reopen_open_mem) {
    char buf[] = "three\n";
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (oc_open_mem(oc, abc_str, abc_str + strlen(abc_str)));
    CHECK (oc_putc(oc, 'a'));
    CHECK (oc_open_mem(oc, one_two_three_str, one_two_three_str + strlen(one_two_three_str)));
    CHECK (oc_putc(oc, 'o'));
    CHECK (oc_puts(oc, "ne\ntwo\n"));
    CHECK (oc_write(oc, buf, strlen(buf)));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}


TEST (reopen_errored_file) {
    char buf[] = "three\n";
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (!oc_putc(oc, 's'));
    CHECK (oc_open_file(oc, "tests/one_two_three"));
    CHECK (oc_putc(oc, 'o'));
    CHECK (oc_puts(oc, "ne\ntwo\n"));
    CHECK (oc_write(oc, buf, strlen(buf)));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (reopen_errored_str) {
    char buf[] = "three\n";
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (oc_open_str(oc, abc_str));
    CHECK (!oc_putc(oc, 's'));
    CHECK (oc_open_str(oc, one_two_three_str));
    CHECK (oc_putc(oc, 'o'));
    CHECK (oc_puts(oc, "ne\ntwo\n"));
    CHECK (oc_write(oc, buf, strlen(buf)));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (reopen_errored_mem) {
    char buf[] = "three\n";
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    CHECK (oc_open_mem(oc, abc_str, abc_str + strlen(abc_str)));
    CHECK (!oc_putc(oc, 's'));
    CHECK (oc_open_mem(oc, one_two_three_str, one_two_three_str + strlen(one_two_three_str)));
    CHECK (oc_putc(oc, 'o'));
    CHECK (oc_puts(oc, "ne\ntwo\n"));
    CHECK (oc_write(oc, buf, strlen(buf)));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (reopen_closed_file,
		  reopen_closed_str,
		  reopen_closed_mem,
		  reopen_open_file,
		  reopen_open_str,
		  reopen_open_mem,
		  reopen_errored_file,
		  reopen_errored_str,
		  reopen_errored_mem);
