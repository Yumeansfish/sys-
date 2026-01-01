#include "basic_testing.h"

#include "../blob.h"


TEST(simple_call_count_char) {
    struct blob b;
    b.sentinel.prev = &(b.sentinel);
    b.sentinel.next = &(b.sentinel);
    count_char(&b, '\0');
    TEST_PASSED;
}

MAIN_TEST_DRIVER()
