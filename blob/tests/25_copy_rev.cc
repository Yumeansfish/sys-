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

TEST(empty_zero1) {
    struct blob b;
    char buf[10];
    make_blob(&b,nullptr,nullptr,0);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 10),==,0);
    TEST_PASSED;
}

TEST(empty_zero2) {
    struct blob b;
    char buf;
    make_blob(&b,nullptr,nullptr,0);
    CHECK_CMP(copy_to_buffer_reverse(&b, &buf, 0),==,0);
    TEST_PASSED;
}

TEST(empty_all_chars) {
    char buf[10];
    struct blob b;
    make_blob(&b,nullptr,nullptr,0);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 10),==,0);
    for (char c = CHAR_MIN; c < CHAR_MAX; ++c)
	CHECK_CMP(count_char(&b, c),==,0);
    TEST_PASSED;
}

TEST(one_zero_length1) {
    char buf[10];
    struct blob b;
    struct chunk_list l[1];
    struct chunk ck[1];
    make_blob(&b, l, ck, 1);
    ck[0].length = 0;
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 10),==,0);
    TEST_PASSED;
}

TEST(one_zero_length2) {
    char buf;
    struct blob b;
    struct chunk_list l[1];
    struct chunk ck[1];
    make_blob(&b, l, ck, 1);
    ck[0].length = 0;
    CHECK_CMP(copy_to_buffer_reverse(&b, &buf, 0),==,0);
    TEST_PASSED;
}

TEST(one_five_chars1) {
    char buf[10];
    struct blob b;
    struct chunk_list l[1];
    struct chunk ck[1];
    make_blob(&b, l, ck, 1);
    ck[0].length = 6;
    ck[0].data[0] = 1;
    ck[0].data[1] = 2;
    ck[0].data[2] = 2;
    ck[0].data[3] = 3;
    ck[0].data[4] = 3;
    ck[0].data[5] = 3;
    memset(buf, 100, 10);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 10),==,6);
    fprintf(stderr,"%d\n",buf[0]);
    CHECK_CMP(buf[0],==,3);
    CHECK_CMP(buf[1],==,3);
    CHECK_CMP(buf[2],==,3);
    CHECK_CMP(buf[3],==,2);
    CHECK_CMP(buf[4],==,2);
    CHECK_CMP(buf[5],==,1);
    CHECK_CMP(buf[6],==,100);
    CHECK_CMP(buf[7],==,100);
    TEST_PASSED;
}

TEST(one_five_chars2) {
    char buf[10];
    struct blob b;
    struct chunk_list l[1];
    struct chunk ck[1];
    make_blob(&b, l, ck, 1);
    ck[0].length = 6;
    ck[0].data[0] = 1;
    ck[0].data[1] = 2;
    ck[0].data[2] = 2;
    ck[0].data[3] = 3;
    ck[0].data[4] = 3;
    ck[0].data[5] = 3;
    memset(buf, 100, 10);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 6),==,6);
    CHECK_CMP(buf[0],==,3);
    CHECK_CMP(buf[1],==,3);
    CHECK_CMP(buf[2],==,3);
    CHECK_CMP(buf[3],==,2);
    CHECK_CMP(buf[4],==,2);
    CHECK_CMP(buf[5],==,1);
    CHECK_CMP(buf[6],==,100);
    CHECK_CMP(buf[7],==,100);
    TEST_PASSED;
}

TEST(one_five_chars3) {
    char buf[10];
    struct blob b;
    struct chunk_list l[1];
    struct chunk ck[1];
    make_blob(&b, l, ck, 1);
    ck[0].length = 6;
    ck[0].data[0] = 1;
    ck[0].data[1] = 2;
    ck[0].data[2] = 2;
    ck[0].data[3] = 3;
    ck[0].data[4] = 3;
    ck[0].data[5] = 3;
    memset(buf, 100, 10);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 5),==,6);
    CHECK_CMP(buf[0],==,3);
    CHECK_CMP(buf[1],==,3);
    CHECK_CMP(buf[2],==,3);
    CHECK_CMP(buf[3],==,2);
    CHECK_CMP(buf[4],==,2);
    CHECK_CMP(buf[5],==,100);
    CHECK_CMP(buf[6],==,100);
    CHECK_CMP(buf[7],==,100);
    TEST_PASSED;
}

TEST(one_five_chars4) {
    char buf[10];
    struct blob b;
    struct chunk_list l[1];
    struct chunk ck[1];
    make_blob(&b, l, ck, 1);
    ck[0].length = 6;
    ck[0].data[0] = 1;
    ck[0].data[1] = 2;
    ck[0].data[2] = 2;
    ck[0].data[3] = 3;
    ck[0].data[4] = 3;
    ck[0].data[5] = 3;
    memset(buf, 100, 10);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 4),==,5);
    CHECK_CMP(buf[0],==,3);
    CHECK_CMP(buf[1],==,3);
    CHECK_CMP(buf[2],==,3);
    CHECK_CMP(buf[3],==,2);
    CHECK_CMP(buf[4],==,100);
    CHECK_CMP(buf[5],==,100);
    CHECK_CMP(buf[6],==,100);
    CHECK_CMP(buf[7],==,100);
    TEST_PASSED;
}

TEST(two_five_chars1) {
    char buf[10];
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

    memset(buf, 100, 10);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 10),==,9);
    CHECK_CMP(buf[0],==,3);
    CHECK_CMP(buf[1],==,2);
    CHECK_CMP(buf[2],==,1);
    CHECK_CMP(buf[3],==,3);
    CHECK_CMP(buf[4],==,3);
    CHECK_CMP(buf[5],==,3);
    CHECK_CMP(buf[6],==,2);
    CHECK_CMP(buf[7],==,2);
    CHECK_CMP(buf[8],==,1);
    CHECK_CMP(buf[9],==,100);
    TEST_PASSED;
}

TEST(two_five_chars2) {
    char buf[10];
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

    memset(buf, 100, 10);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 6),==,7);
    CHECK_CMP(buf[0],==,3);
    CHECK_CMP(buf[1],==,2);
    CHECK_CMP(buf[2],==,1);
    CHECK_CMP(buf[3],==,3);
    CHECK_CMP(buf[4],==,3);
    CHECK_CMP(buf[5],==,3);
    CHECK_CMP(buf[6],==,100);
    CHECK_CMP(buf[7],==,100);
    CHECK_CMP(buf[8],==,100);
    CHECK_CMP(buf[9],==,100);
    TEST_PASSED;
}

TEST(two_five_chars3) {
    char buf[10];
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

    memset(buf, 100, 10);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 9),==,9);
    CHECK_CMP(buf[0],==,3);
    CHECK_CMP(buf[1],==,2);
    CHECK_CMP(buf[2],==,1);
    CHECK_CMP(buf[3],==,3);
    CHECK_CMP(buf[4],==,3);
    CHECK_CMP(buf[5],==,3);
    CHECK_CMP(buf[6],==,2);
    CHECK_CMP(buf[7],==,2);
    CHECK_CMP(buf[8],==,1);
    CHECK_CMP(buf[9],==,100);
    TEST_PASSED;
}

TEST(many_fixed_size_seven_one_to_seven) {
    char buf[100];
    struct blob b;
    struct chunk_list l[50];
    struct chunk ck[50];
    make_blob(&b, l, ck, 50);
    for (int i = 0; i < 50; ++i) {
	ck[i].length = 7;
	for (int j = 0; j < 7; ++j)
	    ck[i].data[j] = j + 1;
    }
    memset(buf, 100, 100);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 99),==,100);
    for (int i = 0; i < 99; ++i)
	CHECK_CMP(buf[i],==, 7 - (i % 7));
    CHECK_CMP(buf[99],==,100);
    TEST_PASSED;
}

TEST(many_variable_size_one_to_seven) {
    char buf[100];
    struct blob b;
    struct chunk_list l[50];
    struct chunk ck[50];
    make_blob(&b, l, ck, 50);
    unsigned int len = 10;
    unsigned int v = 1;
    for (int i = 0; i < 50; ++i) {
	ck[i].length = len;
	for (unsigned int j = 0; j < len; ++j) {
	    ck[i].data[j] = v;
	    if (v == 7)
		v = 1;
	    else
		++v;
	}
	if (len == 0)
	    len = 10;
	else
	    --len;
    }
    memset(buf, 100, 100);
    CHECK_CMP(copy_to_buffer_reverse(&b, buf, 99),==,100);
    // given the somewhat contorted way we build the blob, the last
    // value happens to be 6, so the reverse values should be
    // 6 5 4 3 2 1 7 6 5 4 3 2 1 7 6 ...
    for (int i = 0; i < 99; ++i)
	CHECK_CMP(buf[i],==,7 - ((i+1) % 7));
    CHECK_CMP(buf[99],==,100);
    TEST_PASSED;
}

MAIN_TEST_DRIVER()
