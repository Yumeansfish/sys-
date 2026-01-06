#include <cstring>

#include "basic_testing.h"
#include "../words.h"

#include "random_text.h"

TEST (empty) {
    lines * l = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	add_line (l, line);
    }
    const char * output[1000];
    CHECK (match (l, output, 10, "") == 0);
    lines_destroy (l);
    TEST_PASSED;
}

#define ARRAY_LENGTH(A) (sizeof (A) / sizeof ((A)[0]))

static const char * ac_expected_output[] = {
    "lacinia nostra nunc luctus inceptos ut. Urna sociosqu eu nostra eros",
    "per a a eget sem hac lorem porttitor diam felis quis. Nullam pretium",
    "est varius integer ac maecenas luctus dapibus pellentesque vulputate",
    "aptent conubia quis volutpat finibus accumsan diam per malesuada quam",
    "laoreet nunc potenti molestie fringilla placerat maecenas non",
    "bibendum nisl iaculis nisl. Vel sed massa in posuere rutrum platea. Et",
    "senectus libero class inceptos tempus etiam hac sagittis neque. Enim",
    "nulla lobortis ac. Volutpat consequat convallis suspendisse augue",
    "orci magna pharetra lacinia morbi aenean justo nam odio class",
    "adipiscing morbi urna pellentesque consectetur lacus donec commodo leo",
    "velit habitasse. Laoreet orci quisque vestibulum placerat pharetra ad",
    "lectus eu ante diam himenaeos facilisis sem rutrum sem eros tortor",
    "Interdum aenean mattis sapien lacinia dolor quam pharetra non enim",
    "cubilia. Sed varius mattis convallis laoreet praesent ac porttitor",
    "Platea ad sodales feugiat iaculis tortor diam placerat dolor feugiat",
    "lorem morbi lacinia mi egestas cubilia aliquet suspendisse.",
    "inceptos vulputate morbi a. Gravida consequat justo urna a taciti",
    "praesent dictum id at netus per. Lacinia ante facilisis auctor",
    "senectus nibh ac nisi viverra rutrum nam diam eleifend eu consectetur",
    "iaculis. Aenean ex praesent finibus mauris velit senectus tempor. Vel"
};
static unsigned int ac_expected_count = ARRAY_LENGTH(ac_expected_output);

TEST (ac_unlimited) {
    lines * l = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	add_line (l, line);
    }
    const char * output[1000];
    CHECK_CMP (match (l, output, 1000, "ac"),==,ac_expected_count);
    for (unsigned int i = 0; i < ac_expected_count; ++i)
	CHECK_STRING_CMP (output[i],==,ac_expected_output[i]);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (ac_limited) {
    lines * l = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	add_line (l, line);
    }
    const char * output[1000];
    CHECK_CMP (match (l, output, 10, "ac"),==,10);
    for (unsigned int i = 0; i < 10; ++i)
	CHECK_STRING_CMP (output[i],==,ac_expected_output[i]);
    lines_destroy (l);
    TEST_PASSED;
}

static const char * se_ne_tu_expected_output[] = {
    "consectetur mi ultrices purus nullam neque dictum curabitur sodales",
    "senectus libero class inceptos tempus etiam hac sagittis neque. Enim",
    "non aenean ante senectus ut. Feugiat mollis commodo lobortis suscipit",
    "cubilia sed sollicitudin donec. Odio venenatis sit bibendum maecenas",
    "adipiscing morbi urna pellentesque consectetur lacus donec commodo leo",
    "dictumst mollis. Id senectus malesuada aptent dictum nisl quis",
    "praesent dictum id at netus per. Lacinia ante facilisis auctor",
    "senectus nibh ac nisi viverra rutrum nam diam eleifend eu consectetur",
    "iaculis. Aenean ex praesent finibus mauris velit senectus tempor. Vel"
};

static unsigned int se_ne_tu_expected_count = ARRAY_LENGTH(se_ne_tu_expected_output);

TEST (se_ne_tu_unlimited) {
    lines * l = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	add_line (l, line);
    }
    const char * output[1000];
    CHECK_CMP (match (l, output, 1000, "se ne tu"),==,se_ne_tu_expected_count);
    for (unsigned int i = 0; i < se_ne_tu_expected_count; ++i)
	CHECK_STRING_CMP (output[i],==,se_ne_tu_expected_output[i]);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (se_ne_tu_limited_exact) {
    lines * l = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	add_line (l, line);
    }
    const char * output[1000];
    CHECK_CMP (match (l, output, se_ne_tu_expected_count, "se ne tu"),==,se_ne_tu_expected_count);
    for (unsigned int i = 0; i < se_ne_tu_expected_count; ++i)
	CHECK_STRING_CMP (output[i],==,se_ne_tu_expected_output[i]);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (se_ne_tu_limited_one_less) {
    lines * l = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	add_line (l, line);
    }
    const char * output[1000];
    CHECK_CMP (match (l, output, se_ne_tu_expected_count - 1, "se ne tu"),==,se_ne_tu_expected_count - 1);
    for (unsigned int i = 0; i < se_ne_tu_expected_count - 1; ++i)
	CHECK_STRING_CMP (output[i],==,se_ne_tu_expected_output[i]);
    lines_destroy (l);
    TEST_PASSED;
}

static const char * pellentesque_expected_output[] = {
    "est varius integer ac maecenas luctus dapibus pellentesque vulputate",
    "adipiscing morbi urna pellentesque consectetur lacus donec commodo leo",
};

static unsigned int pellentesque_expected_count = ARRAY_LENGTH(pellentesque_expected_output);

TEST (pellenteque_unlimited) {
    lines * l = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	add_line (l, line);
    }
    const char * output[1000];
    CHECK_CMP (match (l, output, 1000, "pellentesque"),==,pellentesque_expected_count);
    for (unsigned int i = 0; i < pellentesque_expected_count; ++i)
	CHECK_STRING_CMP (output[i],==,pellentesque_expected_output[i]);
    lines_destroy (l);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
