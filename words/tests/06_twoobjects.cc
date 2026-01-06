#include <cstring>
#include <set>

#include "basic_testing.h"
#include "../words.h"

#include "random_text.h"

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

TEST (one_empty_one_full) {
    lines * l1 = lines_create();
    lines * l2 = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	add_line (l1, line);
    }
    const char * output[1000];
    CHECK_CMP (match (l1, output, 1000, "ac"),==,ac_expected_count);
    CHECK_CMP (match (l2, output, 1000, "ac"),==,0);
    lines_destroy (l1);
    lines_destroy (l2);
    TEST_PASSED;
}

TEST (two_different_objects) {
    lines * l1 = lines_create();
    lines * l2 = lines_create();
    char line[1000];
    for (unsigned int i = 0; i < T_length; ++i) {
	strcpy (line, T[i]);
	add_line (l1, line);
    }
    strcpy (line, "one two three");
    int id1 = add_line (l2, line);
    strcpy (line, "four five six");
    int id2 = add_line (l2, line);
    const char * output[1000];
    CHECK_CMP (match (l1, output, 1000, "ac"),==,ac_expected_count);
    CHECK_CMP (match (l2, output, 1000, "ac"),==,0);
    CHECK_CMP (match (l1, output, 1000, "five four"),==,0);
    CHECK_CMP (match (l2, output, 1000, "five four"),==,1);

    CHECK (remove_line (l2, id1));
    CHECK (!remove_line (l2, id1));

    CHECK_CMP (match (l1, output, 1000, "five four"),==,0);
    CHECK_CMP (match (l2, output, 1000, "five four"),==,1);

    CHECK (remove_line (l2, id2));
    CHECK (!remove_line (l2, id2));

    CHECK_CMP (match (l1, output, 1000, "five four"),==,0);
    CHECK_CMP (match (l2, output, 1000, "five four"),==,0);

    lines_destroy (l1);
    lines_destroy (l2);
    TEST_PASSED;
}


MAIN_TEST_DRIVER();
