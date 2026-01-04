#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "s_table.h"

int kg_feature(const char * begin, const char * end) {
    int res = -1;
    char buf[100];
    sscanf(begin, "%100s %dKg", buf, &res);
    return res;
}

int chf_feature(const char * begin, const char * end) {
    int kg;
    int res = -1;
    char buf[100];
    sscanf(begin, "%100s %dKg CHF %d", buf, &kg, &res);
    return res;
}

int false_feature(const char * begin, const char * end) {
    return 0;
}

int true_feature(const char * begin, const char * end) {
    return 1;
}

static const char * tomatoes = "tomatoes 10Kg CHF 55";
static const char * carrots = "carrots 15Kg CHF 40";
static const char * peppers = "peppers 2Kg CHF 6";

int main () {
    char buf[1000];

    struct s_table * t = s_table_new();
    assert(t);
    s_table_delete(t);
    struct s_table * t2 = s_table_new();
    assert(t2);
    t = s_table_new();
    assert(t);
    s_table_delete(t2);

    assert(s_table_remove_record(t, carrots, carrots + strlen(carrots)) == 0);

    assert(s_table_add_record(t, carrots, carrots + strlen(carrots)) != 0);

    // fprintf(stderr,"%d\n",(s_table_remove_record(t, carrots, carrots + strlen(carrots))));
    assert(s_table_remove_record(t, carrots, carrots + strlen(carrots)) == 1);

    assert(s_table_add_record(t, carrots, carrots + strlen(carrots)) != 0);

    assert(s_table_remove_records(t, true_feature) == 1);
    assert(s_table_remove_records(t, true_feature) == 0);

    assert(s_table_add_record(t, carrots, carrots + strlen(carrots)) != 0);

    assert(s_table_remove_records(t, false_feature) == 0);

    assert(s_table_max_feature(t, chf_feature, buf, 1000) == strlen(carrots));
    assert(memcmp(buf, carrots, strlen(carrots)) == 0);
    assert(s_table_max_feature(t, false_feature, buf, 1000) == strlen(carrots));
    assert(memcmp(buf, carrots, strlen(carrots)) == 0);

    s_table_clear(t);

    assert(s_table_add_record(t, peppers, peppers + strlen(peppers)) != 0);
    assert(s_table_max_feature(t, chf_feature, buf, 1000) == strlen(peppers));
    assert(memcmp(buf, peppers, strlen(peppers)) == 0);

    assert(s_table_add_record(t, carrots, carrots + strlen(carrots)) != 0);

    assert(s_table_max_feature(t, chf_feature, buf, 1000) == strlen(carrots));
    assert(memcmp(buf, carrots, strlen(carrots)) == 0);

    assert(s_table_add_record(t, tomatoes, tomatoes + strlen(tomatoes)) != 0);

    assert(s_table_max_feature(t, chf_feature, buf, 1000) == strlen(tomatoes));
    assert(memcmp(buf, tomatoes, strlen(tomatoes)) == 0);

    FILE * f = fmemopen(buf, 1000, "w");

    s_table_print_sorted(t, f, kg_feature);
    
    fclose(f);

    char expected_result[1000];
    sprintf(expected_result, "%s\n%s\n%s\n", peppers, tomatoes, carrots);
    assert(memcmp(buf, expected_result, strlen(expected_result)) == 0);

    s_table_delete(t);
    
    printf("PASSED.\n");
}