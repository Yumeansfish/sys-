#include "basic_testing.h"
#include "../ochecker.h"

TEST (empty_str_to_one_char) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 0;
    CHECK (oc_open_str(oc, buf));
    buf[0] = 'a';
    buf[1] = 0;
    CHECK (!oc_puts(oc,"a"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (empty_mem) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    CHECK (oc_open_mem(oc, buf, buf));
    CHECK (!oc_puts(oc,"a"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (string_change_first) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 0;
    CHECK (oc_open_str(oc, buf));
    buf[0] = 'b';
    CHECK (oc_puts(oc,"a"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (mem_change_first) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    CHECK (oc_open_mem(oc, buf, buf + 1));
    buf[0] = 'b';
    CHECK (oc_puts(oc,"a"));
    oc_destroy(oc);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (empty_str_to_one_char,
		  empty_mem,
		  string_change_first,
		  mem_change_first);
