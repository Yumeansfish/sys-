#include "basic_testing.h"

#include "../wcmp.h"

TEST(simple_call) {
    wcmp("", "");
    TEST_PASSED;
}

MAIN_TEST_DRIVER(simple_call);
