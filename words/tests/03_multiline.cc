#include <cstring>

#include "basic_testing.h"
#include "../words.h"

TEST (two_lines_empty_match) {
    lines * l = lines_create();
    char line[1000];
    strcpy (line, "one two three");
    add_line (l, line);
        fprintf(stderr,"IM here 11");
    strcpy (line, "four five six");
    add_line (l, line);
    const char * output[10];
    fprintf(stderr,"IM here 14");
    CHECK (match (l, output, 10, "") == 0);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (two_lines_no_match) {
    lines * l = lines_create();
    char line[1000];
    strcpy (line, "one two three");
    add_line (l, line);
    strcpy (line, "four five six");
    add_line (l, line);
    const char * output[10];
    CHECK (match (l, output, 10, "seven") == 0);
    lines_destroy (l);
    TEST_PASSED;
}

TEST (two_lines_one_match) {
    lines * l = lines_create();
    char line[1000];
    strcpy (line, "one two three");
    add_line (l, line);
    strcpy (line, "four five six");
    add_line (l, line);
    const char * output[10];
    CHECK (match (l, output, 10, "five") == 1);
    CHECK_STRING_CMP (output[0],==,"four five six");
    lines_destroy (l);
    TEST_PASSED;
}

TEST (two_lines_two_matches) {
    lines * l = lines_create();
    char line[1000];
    strcpy (line, "one two three");
    add_line (l, line);
    strcpy (line, "four five six");
    add_line (l, line);
    const char * output[10];
    CHECK (match (l, output, 10, "e o") == 2);
    CHECK_STRING_CMP (output[0],==,"one two three"); // must match in the order
    CHECK_STRING_CMP (output[1],==,"four five six"); // the lines are added
    lines_destroy (l);
    TEST_PASSED;
}

TEST (two_lines_nospaces_two_matches) {
    lines * l = lines_create();
    char line[1000];
    strcpy (line, "onetwothree");
    add_line (l, line);
    strcpy (line, "fourfivesix");
    add_line (l, line);
    const char * output[10];
    CHECK (match (l, output, 10, "e o") == 2);
    CHECK_STRING_CMP (output[0],==,"onetwothree"); // must match in the order
    CHECK_STRING_CMP (output[1],==,"fourfivesix"); // the lines are added
    lines_destroy (l);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
