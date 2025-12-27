#include "basic_testing.h"
#include "../ochecker.h"

TEST (create_closed) {
    struct ochecker * oc = oc_create();
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (open_empty_file) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/empty_file"));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (open_empty_string) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, ""));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (open_empty_memory) {
    struct ochecker * oc = oc_create();
    char c;
    CHECK (oc_open_mem(oc, &c, &c));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (open_empty_file_eof) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/empty_file"));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (open_empty_string_eof) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, ""));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (open_empty_memory_eof) {
    struct ochecker * oc = oc_create();
    char c;
    CHECK (oc_open_mem(oc, &c, &c));
    CHECK (oc_close(oc));
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (open_empty_file_close) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_file(oc, "tests/empty_file"));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (oc_close(oc));
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (open_empty_string_close) {
    struct ochecker * oc = oc_create();
    CHECK (oc_open_str(oc, ""));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (oc_close(oc));
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    oc_destroy(oc);
    TEST_PASSED;
}

TEST (open_empty_memory_close) {
    struct ochecker * oc = oc_create();
    char c;
    CHECK (oc_open_mem(oc, &c, &c));
    CHECK_CMP (oc_status(oc),==,OC_OPEN);
    CHECK (oc_close(oc));
    CHECK_CMP (oc_status(oc),==,OC_CLOSED);
    oc_destroy(oc);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (create_closed,
		  open_empty_file,
		  open_empty_string,
		  open_empty_memory,
		  open_empty_file_eof,
		  open_empty_string_eof,
		  open_empty_memory_eof,
		  open_empty_file_close,
		  open_empty_string_close,
		  open_empty_memory_close)
