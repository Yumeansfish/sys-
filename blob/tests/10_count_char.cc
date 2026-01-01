#include <climits>

#include "basic_testing.h"

#include "../blob.h"

static void make_blob(struct blob * b, struct chunk_list * l, struct chunk * c, unsigned int n) {
    b->sentinel.prev = &(b->sentinel);
    b->sentinel.next = &(b->sentinel);
    for (unsigned int i = 0; i < n; ++i) {
	l->prev = b->sentinel.prev;
	l->next = &(b->sentinel);
	l->prev->next = l;
	l->next->prev = l;
	l->c = c;
	++l;
	++c;
    }
}

TEST(empty_zero) {
    struct blob b;
    make_blob(&b,nullptr,nullptr,0);
    CHECK_CMP(count_char(&b, '\0'),==,0);
    TEST_PASSED;
}

TEST(empty_all_chars) {
    struct blob b;
    make_blob(&b,nullptr,nullptr,0);
    for (char c = CHAR_MIN; c < CHAR_MAX; ++c)
	CHECK_CMP(count_char(&b, c),==,0);
    TEST_PASSED;
}

TEST(one_zero_length_all_chars) {
    struct blob b;
    struct chunk_list l[1];
    struct chunk ck[1];
    make_blob(&b, l, ck, 1);
    ck[0].length = 0;
    for (char c = CHAR_MIN; c < CHAR_MAX; ++c)
	CHECK_CMP(count_char(&b, c),==,0);
    TEST_PASSED;
}

TEST(one_five_chars) {
    struct blob b;
    struct chunk_list l[1];
    struct chunk ck[1];
    make_blob(&b, l, ck, 1);
    ck[0].length = 0;
    ck[0].length = 6;
    ck[0].data[0] = 1;
    ck[0].data[1] = 2;
    ck[0].data[2] = 2;
    ck[0].data[3] = 3;
    ck[0].data[4] = 3;
    ck[0].data[5] = 3;
    CHECK_CMP(count_char(&b, 3),==,3);
    CHECK_CMP(count_char(&b, 2),==,2);
    CHECK_CMP(count_char(&b, 1),==,1);
    TEST_PASSED;
}

TEST(two_five_chars) {
    struct blob b;
    struct chunk_list l[2];
    struct chunk ck[2];
    make_blob(&b, l, ck, 2);
    ck[0].length = 6;
    ck[0].data[0] = 1;
    ck[0].data[1] = 2;
    ck[0].data[2] = 2;
    ck[0].data[3] = 3;
    ck[0].data[4] = 3;
    ck[0].data[5] = 3;
    ck[1].length = 3;
    ck[1].data[0] = 1;
    ck[1].data[1] = 2;
    ck[1].data[2] = 3;

    CHECK_CMP(count_char(&b, 3),==,4);
    CHECK_CMP(count_char(&b, 2),==,3);
    CHECK_CMP(count_char(&b, 1),==,2);
    TEST_PASSED;
}

TEST(many_fixed_size_seven_one_to_seven1) {
    struct blob b;
    struct chunk_list l[50];
    struct chunk ck[50];
    make_blob(&b, l, ck, 50);
    for (int i = 0; i < 50; ++i) {
	ck[i].length = 7;
	for (int j = 0; j < 7; ++j)
	    ck[i].data[j] = j + 1;
    }
    for (char c = CHAR_MIN; c < CHAR_MAX; ++c) {
	if (c >= 1 && c <= 7) {
	    CHECK_CMP(count_char(&b, c),==,50);
	} else {
	    CHECK_CMP(count_char(&b, c),==,0);
	}
    }
    TEST_PASSED;
}

TEST(many_fixed_size_seven_one_to_seven2) {
    struct blob b;
    struct chunk_list l[50];
    struct chunk ck[50];
    make_blob(&b, l, ck, 50);
    for (int i = 0; i < 50; ++i) {
	ck[i].length = 7;
	for (int j = 0; j < 7; ++j)
	    ck[i].data[j] = j + 1;
    }
    ck[10].length = 0;
    ck[11].length = 0;
    for (char c = CHAR_MIN; c < CHAR_MAX; ++c) {
	if (c >= 1 && c <= 7) {
	    CHECK_CMP(count_char(&b, c),==,48);
	} else {
	    CHECK_CMP(count_char(&b, c),==,0);
	}
    }
    TEST_PASSED;
}

MAIN_TEST_DRIVER()
