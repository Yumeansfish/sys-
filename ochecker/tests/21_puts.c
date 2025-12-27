#include "basic_testing.h"
#include "../ochecker.h"

TEST (puts_on_empty_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/empty_file"));
    CHECK (!oc_puts(oc,"a"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_on_empty_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, ""));
    CHECK (!oc_puts(oc,"a"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_on_empty_memory) {
    struct ochecker * oc = oc_create();
    char c;
    CHECK (oc_open_mem(oc, &c, &c));
    CHECK (!oc_puts(oc,"a"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_on_abc_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_puts(oc,"a"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_on_abc_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK (oc_puts(oc,"a"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK (oc_puts(oc,"a"));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_three_on_abc_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_puts(oc,"a"));
    CHECK (oc_puts(oc,"b"));
    CHECK (oc_puts(oc,"c"));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_three_on_abc_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK (oc_puts(oc,"a"));
    CHECK (oc_puts(oc,"b"));
    CHECK (oc_puts(oc,"c"));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_three_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK (oc_puts(oc,"a"));
    CHECK (oc_puts(oc,"b"));
    CHECK (oc_puts(oc,"c"));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_whole_on_abc_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_puts(oc,"abc"));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_whole_on_abc_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK (oc_puts(oc,"abc"));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_whole_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK (oc_puts(oc,"abc"));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_empty_on_abc_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    for (int i = 0; i < 10; ++i)
	CHECK (oc_puts(oc,""));
    CHECK (oc_puts(oc,"abc"));
    CHECK (oc_puts(oc,""));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_empty_on_abc_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    for (int i = 0; i < 10; ++i)
	CHECK (oc_puts(oc,""));
    CHECK (oc_puts(oc,"abc"));
    CHECK (oc_puts(oc,""));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (puts_empty_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    for (int i = 0; i < 10; ++i)
	CHECK (oc_puts(oc,""));
    CHECK (oc_puts(oc,"abc"));
    CHECK (oc_puts(oc,""));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (puts_on_empty_file,
		  puts_on_empty_str,
		  puts_on_empty_memory,
		  puts_on_abc_file,
		  puts_on_abc_str,
		  puts_on_abc_memory,
		  puts_three_on_abc_file,
		  puts_three_on_abc_str,
		  puts_three_on_abc_memory,
		  puts_whole_on_abc_file,
		  puts_whole_on_abc_str,
		  puts_whole_on_abc_memory,
		  puts_empty_on_abc_file,
		  puts_empty_on_abc_str,
		  puts_empty_on_abc_memory);
