#include "basic_testing.h"
#include "../ochecker.h"

TEST (putc_on_empty_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/empty_file"));
    CHECK (!oc_putc(oc,'a'));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_on_empty_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, ""));
    CHECK (!oc_putc(oc,'a'));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_on_empty_memory) {
    struct ochecker * oc = oc_create();
    char c;
    CHECK (oc_open_mem(oc, &c, &c));
    CHECK (!oc_putc(oc,'a'));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_on_abc_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_putc(oc,'a'));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_on_abc_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK (oc_putc(oc,'a'));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK (oc_putc(oc,'a'));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_three_on_abc_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_putc(oc,'a'));
    CHECK (oc_putc(oc,'b'));
    CHECK (oc_putc(oc,'c'));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_three_on_abc_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK (oc_putc(oc,'a'));
    CHECK (oc_putc(oc,'b'));
    CHECK (oc_putc(oc,'c'));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (putc_three_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK (oc_putc(oc,'a'));
    CHECK (oc_putc(oc,'b'));
    CHECK (oc_putc(oc,'c'));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (putc_on_empty_file,
		  putc_on_empty_str,
		  putc_on_empty_memory,
		  putc_on_abc_file,
		  putc_on_abc_str,
		  putc_on_abc_memory,
		  putc_three_on_abc_file,
		  putc_three_on_abc_str,
		  putc_three_on_abc_memory);
