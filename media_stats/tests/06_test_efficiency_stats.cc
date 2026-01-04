#include <cstdio>

#include "basic_testing.h"

#include "../media_stats.h"

int views = 0;

static const int mcount = 432;
static const int ucount = 123;
static const int vcount = 100;

static void populate_database() {
    for (int i = 0; i < mcount; ++i) {
	char media[20];
	sprintf(media, "m%d", i);
	add_media(media, 100.0 + 100.0*i/(mcount - 1));
	for (int j = 0; j < ucount; ++j) {
	    char user[20];
	    sprintf(user, "u%d", j);
	    for (int k = 0; k < vcount; ++k) 
		add_view(media, user, k*50.0/vcount, k*50.0/vcount + 20.0);
	}
    }
}

TEST(many_views) {
    populate_database(); 
    for (int i = 0; i < mcount; ++i) {
	char media[20];
	sprintf(media, "m%d", i);
	views += complete_views(media);
    }
    clear_media();
    TEST_PASSED;
}

int viewers = 0;

TEST(many_viewers) {
    populate_database();
    for (int i = 0; i < mcount; ++i) {
	char media[20];
	sprintf(media, "m%d", i);
	viewers += unique_viewers(media);
    }
    clear_media();
    TEST_PASSED;
}

TEST(many_time_viewed) {
    populate_database();
    for (int i = 0; i < mcount; ++i) {
	char media[20];
	sprintf(media, "m%d", i);
	for (int j = 0; j < ucount; ++j) {
	    char user[20];
	    sprintf(user, "u%d", j);
	    views += total_time_viewed(media, user);
	}
    }
    clear_media();
    TEST_PASSED;
}

MAIN_TEST_DRIVER(many_views,
		 many_viewers,
		 many_time_viewed)
