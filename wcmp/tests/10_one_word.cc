#include "basic_testing.h"

#include "../wcmp.h"

TEST(both_empty) {
    CHECK_CMP(wcmp("", ""),==,0);
    TEST_PASSED;
}

TEST(b_empty1) {
    CHECK_CMP(wcmp("x", ""),==,1);
    TEST_PASSED;
}

TEST(b_empty2) {
    CHECK_CMP(wcmp("ciao", ""),==,1);
    TEST_PASSED;
}

TEST(a_empty1) {
    CHECK_CMP(wcmp("", "y"),==,-1);
    TEST_PASSED;
}

TEST(a_empty2) {
    CHECK_CMP(wcmp("", "mamma"),==,-1);
    TEST_PASSED;
}

TEST(equals1) {
    CHECK_CMP(wcmp("mamma", "mamma"),==,0);
    TEST_PASSED;
}

TEST(equals2) {
    CHECK_CMP(wcmp("ciao", "ciao"),==,0);
    TEST_PASSED;
}

TEST(equals3) {
    CHECK_CMP(wcmp("ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao",
		   "ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao"),==,0);
    TEST_PASSED;
}

TEST(less_than1) {
    CHECK_CMP(wcmp("ciao", "mamma"),==,-1);
    TEST_PASSED;
}

TEST(less_than2) {
    CHECK_CMP(wcmp("ciao", "ciaomamma"),==,-1);
    TEST_PASSED;
}

TEST(less_than3) {
    CHECK_CMP(wcmp("ciaomamma", "ciaopapa"),==,-1);
    TEST_PASSED;
}

TEST(less_than4) {
    CHECK_CMP(wcmp("ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaocia",
		   "ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao"),==,-1);
    TEST_PASSED;
}

TEST(greater_than1) {
    CHECK_CMP(wcmp("mamma", "ciao"),==,1);
    TEST_PASSED;
}

TEST(greater_than2) {
    CHECK_CMP(wcmp("ciaomamma", "ciao"),==,1);
    TEST_PASSED;
}

TEST(greater_than3) {
    CHECK_CMP(wcmp("ciaopapa", "ciaomamma"),==,1);
    TEST_PASSED;
}

TEST(greater_than4) {
    CHECK_CMP(wcmp("ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaociao", "ciaociaociaociaociaociaociaociaociaociaociaociaociaociaociaocia"),==,1);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(both_empty,
		 b_empty1,
		 b_empty2,
		 a_empty1,
		 a_empty2,
		 equals1,
		 equals2,
		 equals3,
		 less_than1,
		 less_than2,
		 less_than3,
		 less_than4,
		 greater_than1,
		 greater_than2,
		 greater_than3,
		 greater_than4)

