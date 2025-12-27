#include <stddef.h>

#include "basic_testing.h"
#include "../ochecker.h"

TEST (nop) {
    struct ochecker * oc = oc_create();
    CHECK (oc != NULL);
    oc_destroy(oc);
    TEST_PASSED;
}

MAIN_TEST_DRIVER (nop);
