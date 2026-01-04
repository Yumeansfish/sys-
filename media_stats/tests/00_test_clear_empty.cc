#include "basic_testing.h"

#include "../media_stats.h"

TEST(clear_media_empty) {
    clear_media();
    TEST_PASSED;
}

TEST(clear_views_empty) {
    clear_views();
    TEST_PASSED;
}

MAIN_TEST_DRIVER(clear_media_empty,
		 clear_views_empty)
