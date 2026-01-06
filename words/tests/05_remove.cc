#include <cstring>
#include <set>

#include "basic_testing.h"
#include "../words.h"

#include "random_text.h"

TEST (unique_line_ids) {
    std::set<int> S;
    lines * l = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	S.insert(add_line (l, line));
    }
    CHECK_CMP (S.size(),==,T_length); // add_line must return unique ids
    lines_destroy (l);
    TEST_PASSED;
}

TEST (return_values) {
    std::set<int> S;
    lines * l = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	S.insert(add_line (l, line));
    }
    int id = *S.begin();
    CHECK (remove_line(l, id));
    CHECK (!remove_line(l, id));
    int id_max = *S.rbegin() + 1;
    CHECK (!remove_line(l, id_max));
    CHECK (remove_line(l, id_max - 1));
    CHECK (!remove_line(l, id_max - 1));
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

TEST (ac_remove_all) {
    std::set<int> S;
    lines * l = lines_create();
    for (unsigned int i = 0; i < T_length; ++i) {
	char line[1000];
	strcpy (line, T[i]);
	S.insert(add_line (l, line));
    }
    const char * output[1000];
    CHECK_CMP (match (l, output, 1000, "ac"),==,ac_expected_count);
    for (int id : S)
	remove_line(l, id);
    CHECK_CMP (match (l, output, 1000, "ac"),==,0);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (ac_remove_all_10000_times) {
    lines * l = lines_create();
    for (int t = 0; t < 10000; ++t) {
	std::set<int> S;
	for (unsigned int i = 0; i < T_length; ++i) {
	    char line[1000];
	    strcpy (line, T[i]);
	    S.insert(add_line (l, line));
	}
	const char * output[1000];
	CHECK_CMP (match (l, output, 1000, "ac"),==,ac_expected_count);
	for (int id : S)
	    remove_line(l, id);
	CHECK_CMP (match (l, output, 1000, "ac"),==,0);
    }
    lines_destroy (l);
    TEST_PASSED;
}

static const char * pellentesque_expected_output[] = {
    "est varius integer ac maecenas luctus dapibus pellentesque vulputate",
    "adipiscing morbi urna pellentesque consectetur lacus donec commodo leo",
};

static const int pellentesque_line0_idx = 3;
static const int pellentesque_line1_idx = 37;

TEST (pellenteque_remove_and_add) {
    lines * l = lines_create();
    int id0 = 0, id1 = 0;
    char line[1000];
    for (unsigned int i = 0; i < T_length; ++i) {
	strcpy (line, T[i]);
	int id = add_line (l, line);
	if (i == pellentesque_line0_idx)
	    id0 = id;
	else if (i == pellentesque_line1_idx)
	    id1 = id;
    }
    const char * output[1000];

    remove_line(l, id0);
    CHECK_CMP (match (l, output, 1000, "pellentesque"),==,1);
    CHECK_STRING_CMP (output[0],==,pellentesque_expected_output[1]);
    remove_line(l, id0);
    strcpy (line, T[pellentesque_line0_idx]);
    id0 = add_line (l, line);
    CHECK_CMP (match (l, output, 1000, "pellentesque"),==,2);
    CHECK_STRING_CMP (output[0],==,pellentesque_expected_output[1]);
    CHECK_STRING_CMP (output[1],==,pellentesque_expected_output[0]);
    remove_line(l, id1);
    CHECK_CMP (match (l, output, 1000, "pellentesque"),==,1);
    CHECK_STRING_CMP (output[0],==,pellentesque_expected_output[0]);
    remove_line(l, id0);
    CHECK_CMP (match (l, output, 1000, "pellentesque"),==,0);

    lines_destroy (l);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
