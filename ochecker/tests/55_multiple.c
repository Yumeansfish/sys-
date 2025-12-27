#include "basic_testing.h"
#include "../ochecker.h"
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

static size_t size = 1000;

TEST (multiple_files_open) {
    struct ochecker * checkers[size];

    for (size_t i = 0; i < size; ++i) {
	checkers[i] = oc_create();
	CHECK (checkers[i] != NULL);
	CHECK_CMP (oc_status(checkers[i]),==,OC_CLOSED);
	CHECK (oc_open_file(checkers[i], "tests/abc_file"));
    }

    for (size_t i = 0; i < size; ++i)
	CHECK (oc_puts(checkers[i], "abc"));

    for (size_t i = 0; i < size; ++i)
	CHECK_CMP (oc_status (checkers[i]),==,OC_OPEN);

    for (size_t i = 0; i < size; ++i)
	oc_destroy(checkers[i]);

    TEST_PASSED;
}

TEST (multiple_str_open) {
    struct ochecker * checkers[size];

    for (size_t i = 0; i < size; ++i) {
	checkers[i] = oc_create();
	CHECK (checkers[i]  != NULL);
	CHECK_CMP (oc_status(checkers[i]),==,OC_CLOSED);
	CHECK (oc_open_str(checkers[i], "abc"));
    }

    for (size_t i = 0; i < size; ++i)
	CHECK (oc_puts(checkers[i], "abc"));

    for (size_t i = 0; i < size; ++i)
	CHECK_CMP (oc_status (checkers[i]),==,OC_OPEN);

    for (size_t i = 0; i < size; ++i)
	oc_destroy(checkers[i]);

    TEST_PASSED;
}


TEST (multiple_mem_open) {
    char buf[] = "abc";
    struct ochecker * checkers[size];

    for (size_t i = 0; i < size; ++i) {
	checkers[i] = oc_create();
	CHECK (checkers[i] != NULL);
	CHECK_CMP (oc_status(checkers[i]),==,OC_CLOSED);
	CHECK (oc_open_mem(checkers[i], buf, buf + strlen(buf)));
    }

    for (size_t i = 0; i < size; ++i)
	CHECK (oc_puts(checkers[i], "abc"));

    for (size_t i = 0; i < size; ++i)
	CHECK_CMP (oc_status (checkers[i]),==,OC_OPEN);

    for (size_t i = 0; i < size; ++i)
	oc_destroy(checkers[i]);

    TEST_PASSED;
}

TEST (multiple_files_errored) {
    struct ochecker * checkers[size];

    for (size_t i = 0; i < size; ++i) {
	checkers[i] = oc_create();
	CHECK (checkers[i] != NULL);
	CHECK_CMP (oc_status(checkers[i]),==,OC_CLOSED);
	CHECK (oc_open_file(checkers[i], "tests/abc_file"));
    }

    for (size_t i = 0; i < size; ++i)
	CHECK (!oc_putc(checkers[i], 's'));

    for (size_t i = 0; i < size; ++i)
	CHECK_CMP (oc_status (checkers[i]),==,OC_ERROR);

    for (size_t i = 0; i < size; ++i)
	oc_destroy(checkers[i]);

    TEST_PASSED;
}

TEST (multiple_str_errored) {
    struct ochecker * checkers[size];

    for (size_t i = 0; i < size; ++i) {
	checkers[i] = oc_create();
	CHECK (checkers[i]  != NULL);
	CHECK_CMP (oc_status(checkers[i]),==,OC_CLOSED);
	CHECK (oc_open_str(checkers[i], "abc"));
    }

    for (size_t i = 0; i < size; ++i)
	CHECK (!oc_putc(checkers[i], 's'));

    for (size_t i = 0; i < size; ++i)
	CHECK_CMP (oc_status (checkers[i]),==,OC_ERROR);

    for (size_t i = 0; i < size; ++i)
	oc_destroy(checkers[i]);

    TEST_PASSED;
}

TEST (multiple_mem_errored) {
    char buf[] = "abc";
    struct ochecker * checkers[size];

    for (size_t i = 0; i < size; ++i) {
	checkers[i] = oc_create();
	CHECK (checkers[i] != NULL);
	CHECK_CMP (oc_status(checkers[i]),==,OC_CLOSED);
	CHECK (oc_open_mem(checkers[i], buf, buf + strlen(buf)));
    }

    for (size_t i = 0; i < size; ++i)
	CHECK (!oc_putc(checkers[i], 's'));

    for (size_t i = 0; i < size; ++i)
	CHECK_CMP (oc_status (checkers[i]),==,OC_ERROR);

    for (size_t i = 0; i < size; ++i)
	oc_destroy(checkers[i]);

    TEST_PASSED;
}

TEST (multiple_output_checker_types) {
    char buf[] = "one\ntwo\nthree\n";
    struct ochecker * checkers[size];

    srand(time(NULL));
    
    for (size_t i = 0; i < size; ++i) {
	checkers[i] = oc_create();
	CHECK (checkers[i] != NULL);
	CHECK_CMP (oc_status(checkers[i]),==,OC_CLOSED);

	int v = rand()%3;
	if (v == 0) {
	    CHECK (oc_open_file(checkers[i], "tests/one_two_three"));
	} else if (v == 1) {
	    CHECK (oc_open_str(checkers[i], buf));
	} else {
	    CHECK (oc_open_mem(checkers[i], buf, buf + strlen(buf)));
	}
    }

    for (size_t i = 0; i < size; ++i) {
	CHECK (oc_putc(checkers[i], 'o'));
	CHECK (oc_puts(checkers[i], "ne\ntwo\n"));
	CHECK (oc_write(checkers[i], buf + 8, 6));
    }

    for (size_t i = 0; i < size; ++i)
	oc_destroy(checkers[i]);
    
    TEST_PASSED;
}

TEST (multiple_rand_str) {
    struct ochecker * checkers[size];
    int len = 100;
    char str[size][len];

    srand(time(NULL));

    for (size_t i = 0; i < size; ++i) {
	int v = rand()%len;
	for (int j = 0; j < v; ++j)
	    str[i][j] = 'A' + rand()%('Z'-'A' + 1);
	str[i][v] = '\0';
    }

    for (size_t i = 0; i < size; ++i) {
	checkers[i] = oc_create();
	CHECK (checkers[i]  != NULL);
	CHECK_CMP (oc_status(checkers[i]),==,OC_CLOSED);
	CHECK (oc_open_str(checkers[i], str[i]));
    }

    for (size_t i = 0; i < size; ++i)
	CHECK (oc_puts(checkers[i], str[i]));

    for (size_t i = 0; i < size; ++i)
	oc_destroy(checkers[i]);

    TEST_PASSED;
}

TEST (multiple_rand_mem) {
    struct ochecker * checkers[size];
    int len = 100;
    char str[size][len];
    int lengths[size];

    srand(time(NULL));

    for (size_t i = 0; i < size; ++i) {
	lengths[i] = rand()%len;
	for (int j = 0; j < lengths[i]; ++j)
	    str[i][j] = 'A' + rand()%('Z'-'A' + 1);
    }

    for (size_t i = 0; i < size; ++i) {
	checkers[i] = oc_create();
	CHECK (checkers[i] != NULL);
	CHECK_CMP (oc_status(checkers[i]),==,OC_CLOSED);
	CHECK (oc_open_mem(checkers[i], str[i], str[i] + lengths[i]));
    }

    for (size_t i = 0; i < size; ++i)
	CHECK (oc_write(checkers[i], str[i], lengths[i]));

    for (size_t i = 0; i < size; ++i)
	oc_destroy(checkers[i]);

    TEST_PASSED;
}

MAIN_TEST_DRIVER (multiple_files_open,
		  multiple_str_open,
		  multiple_mem_open,
		  multiple_files_errored,
		  multiple_str_errored,
		  multiple_mem_errored,
		  multiple_output_checker_types,
		  multiple_rand_str,
		  multiple_rand_mem);
