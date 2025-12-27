#include "basic_testing.h"
#include "../ochecker.h"

static const char * abc_buf = "abcdef";

TEST (write_on_empty_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/empty_file"));
    CHECK (!oc_write(oc, abc_buf, 1));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_on_empty_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, ""));
    CHECK (!oc_write(oc, abc_buf, 1));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_on_empty_memory) {
    struct ochecker * oc = oc_create();
    char c;
    CHECK (oc_open_mem(oc, &c, &c));
    CHECK (!oc_write(oc, abc_buf, 1));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_on_abc_file) {
    char buf[10];
    memcpy(buf, "abcdefghij", 10);
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_write(oc, abc_buf, 1));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_on_abc_str) {
    char buf[10];
    memcpy(buf, "abcdefghij", 10);
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK (oc_write(oc, abc_buf, 1));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK (oc_write(oc, abc_buf, 1));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_three_on_abc_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_write(oc, abc_buf, 1));
    CHECK (oc_write(oc, abc_buf + 1, 1));
    CHECK (oc_write(oc, abc_buf + 2, 1));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_three_on_abc_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK (oc_write(oc, abc_buf, 1));
    CHECK (oc_write(oc, abc_buf + 1, 1));
    CHECK (oc_write(oc, abc_buf + 2, 1));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_three_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK (oc_write(oc, abc_buf, 1));
    CHECK (oc_write(oc, abc_buf + 1, 1));
    CHECK (oc_write(oc, abc_buf + 2, 1));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_whole_on_abc_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_write(oc, abc_buf, 3));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_whole_on_abc_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK (oc_write(oc, abc_buf, 3));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_whole_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK (oc_write(oc, abc_buf, 3));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_empty_on_abc_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    for (int i = 0; i < 10; ++i)
	CHECK (oc_write(oc, abc_buf, 0));
    CHECK (oc_write(oc, abc_buf, 3));
    CHECK (oc_write(oc, abc_buf, 0));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_empty_on_abc_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    for (int i = 0; i < 10; ++i)
	CHECK (oc_write(oc, abc_buf, 0));
    CHECK (oc_write(oc, abc_buf, 3));
    CHECK (oc_write(oc, abc_buf, 0));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_empty_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    for (int i = 0; i < 10; ++i)
	CHECK (oc_write(oc, abc_buf, 0));
    CHECK (oc_write(oc, abc_buf, 3));
    CHECK (oc_write(oc, abc_buf, 0));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_too_much_on_abc_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/abc_file"));
    CHECK (oc_write(oc, abc_buf, 1));
    CHECK (!oc_write(oc, abc_buf + 1, 3));
    CHECK (!oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_too_much_on_abc_str) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, "abc"));
    CHECK (oc_write(oc, abc_buf, 1));
    CHECK (!oc_write(oc, abc_buf + 1, 3));
    CHECK (!oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (write_too_much_on_abc_memory) {
    struct ochecker * oc = oc_create();
    char buf[10];
    buf[0] = 'a';
    buf[1] = 'b';
    buf[2] = 'c';
    CHECK (oc_open_mem(oc, buf, buf + 3));
    CHECK (oc_write(oc, abc_buf, 1));
    CHECK (!oc_write(oc, abc_buf + 1, 3));
    CHECK (!oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (write_on_empty_file,
		  write_on_empty_str,
		  write_on_empty_memory,
		  write_on_abc_file,
		  write_on_abc_str,
		  write_on_abc_memory,
		  write_three_on_abc_file,
		  write_three_on_abc_str,
		  write_three_on_abc_memory,
		  write_whole_on_abc_file,
		  write_whole_on_abc_str,
		  write_whole_on_abc_memory,
		  write_empty_on_abc_file,
		  write_empty_on_abc_str,
		  write_too_much_on_abc_memory,
		  write_too_much_on_abc_file,
		  write_too_much_on_abc_str,
		  write_too_much_on_abc_memory);
