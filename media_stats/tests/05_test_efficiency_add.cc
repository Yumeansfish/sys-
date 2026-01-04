#include <cstdio>

#include "basic_testing.h"

#include "../media_stats.h"

TEST(many_media) {
    for (int i = 0; i < 1234; ++i) {
	char buf[20];
	sprintf(buf, "media%d", i);
	CHECK_CMP(add_media(buf,1.0), ==, 1);
    }
    clear_media();
    TEST_PASSED;
}

TEST(media_users_one_view) {
    static const int mcount = 1234;
    static const int ucount = 1234;
    for (int i = 0; i < mcount; ++i) {
	char media[20];
	sprintf(media, "m%d", i);
	CHECK_CMP(add_media(media, 100.0 + 100.0*i/(mcount - 1)), ==, 1);
	for (int j = 0; j < ucount; ++j) {
	    char user[20];
	    sprintf(user, "u%d", j);
	    CHECK_CMP(add_view(media, user, 0.0, 100.0), ==, 1);
	}
    }
    clear_media();
    TEST_PASSED;
}

TEST(media_users_one_view_repeated) {
    static const int mcount = 1234;
    static const int ucount = 123;
    for (int n = 0; n < 10; ++n) {
	for (int i = 0; i < mcount; ++i) {
	    char media[20];
	    sprintf(media, "m%d", i);
	    CHECK_CMP(add_media(media, 100.0 + 100.0*i/(mcount - 1)), ==, 1);
	    for (int j = 0; j < ucount; ++j) {
		char user[20];
		sprintf(user, "u%d", j);
		CHECK_CMP(add_view(media, user, 0.0, 100.0), ==, 1);
	    }
	}
	clear_media();
    }
    TEST_PASSED;
}

TEST(media_users_views) {
    static const int mcount = 432;
    static const int ucount = 123;
    static const int vcount = 100;
    for (int i = 0; i < mcount; ++i) {
	char media[20];
	sprintf(media, "m%d", i);
	CHECK_CMP(add_media(media, 100.0 + 100.0*i/(mcount - 1)), ==, 1);
	for (int j = 0; j < ucount; ++j) {
	    char user[20];
	    sprintf(user, "u%d", j);
	    for (int k = 0; k < vcount; ++k) 
		CHECK_CMP(add_view(media, user, k*50.0/vcount, k*50.0/vcount + 20.0), ==, 1);
	}
    }
    clear_media();
    TEST_PASSED;
}

TEST(media_users_views_repeated) {
    static const int mcount = 123;
    static const int ucount = 123;
    static const int vcount = 100;
    for (int n = 0; n < 10; ++n) {
	for (int i = 0; i < mcount; ++i) {
	    char media[20];
	    sprintf(media, "m%d", i);
	    CHECK_CMP(add_media(media, 100.0 + 100.0*i/(mcount - 1)), ==, 1);
	    for (int j = 0; j < ucount; ++j) {
		char user[20];
		sprintf(user, "u%d", j);
		for (int k = 0; k < vcount; ++k) 
		    CHECK_CMP(add_view(media, user, k*50.0/vcount, k*50.0/vcount + 20.0), ==, 1);
	    }
	}
	clear_media();
    }
    TEST_PASSED;
}

TEST(media_users_views_repeated2) {
    static const int mcount = 123;
    static const int ucount = 123;
    static const int vcount = 100;
    for (int i = 0; i < mcount; ++i) {
	char media[20];
	sprintf(media, "m%d", i);
	CHECK_CMP(add_media(media, 100.0 + 100.0*i/(mcount - 1)), ==, 1);
    }
    for (int n = 0; n < 10; ++n) {
	for (int i = 0; i < mcount; ++i) {
	    char media[20];
	    sprintf(media, "m%d", i);
	    for (int j = 0; j < ucount; ++j) {
		char user[20];
		sprintf(user, "u%d", j);
		for (int k = 0; k < vcount; ++k) 
		    CHECK_CMP(add_view(media, user, k*50.0/vcount, k*50.0/vcount + 20.0), ==, 1);
	    }
	    clear_views();
	}
    }
    clear_media();
    TEST_PASSED;
}

MAIN_TEST_DRIVER(many_media,
		 media_users_one_view,
		 media_users_one_view_repeated,
		 media_users_views,
		 media_users_views_repeated,
		 media_users_views_repeated2)

