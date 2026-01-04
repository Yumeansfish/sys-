#include <assert.h>
#include <string.h>
#include<stdio.h>

#include "../rec_io.h"

static char buf[2000];


int main() {
    fprintf(stderr,"Im here 11\n");
    struct rec_io * r = rec_io_new();
    fprintf(stderr,"Im here 13\n");
    assert(r);
    fprintf(stderr,"Im here 15\n");
    rec_io_destroy(r);

    fprintf(stderr,"Im here 17\n");
    r = rec_io_new();
    fprintf(stderr,"Im here 20\n");
    assert(r);

    const char s1[] = "ciao mamma, come stai?";
    size_t s1_len = sizeof(s1) - 1;

    const char s2[] = "ciao";

    fprintf(stderr,"Im here 28\n");
    assert(rec_io_read_record(r, s2, s2 + 4) == 1);
    fprintf(stderr,"Im here 31\n");
    fprintf(stderr,"%zu\n",rec_io_write_record(r, buf, 2000, "_%0_"));
    assert(rec_io_write_record(r, buf, 2000, "_%0_") == 6);
    fprintf(stderr,"Im here 33\n");
    fprintf(stderr,"%s\n",buf);
    assert(memcmp(buf, "_ciao_", 6) == 0);

    fprintf(stderr,"Im here 36\n");
    fprintf(stderr,"%d\n",rec_io_read_record(r,s1,s1+s1_len));
    assert(rec_io_read_record(r, s1, s1 + s1_len) == 4);
    fprintf(stderr,"Im here 38\n");
    assert(rec_io_write_record(r, buf, 2000, "ciao ciao!") == 10);
    fprintf(stderr,"Im here 40\n");
    assert(memcmp(buf, "ciao ciao!", 10) == 0);

    fprintf(stderr,"Im here 43\n");
    fprintf(stderr,"%zu\n",(rec_io_write_record(r, buf, 2000, "%1")));
    fprintf(stderr,"%s\n",buf);
    assert(rec_io_write_record(r, buf, 2000, "%1") == 6);
    fprintf(stderr,"Im here 45\n");
    assert(memcmp(buf, "mamma,", 6) == 0);

    fprintf(stderr,"Im here 48\n");
    assert(rec_io_write_record(r, buf, 2000, "%3") == 5);
    fprintf(stderr,"Im here 50\n");
    assert(memcmp(buf, "stai?", 5) == 0);

    fprintf(stderr,"Im here 53\n");
    assert(rec_io_write_record(r, buf, 2000, "ciao %1 come %3") == 22);
    fprintf(stderr,"Im here 55\n");
    assert(memcmp(buf, s1, 22) == 0);

    const char * sep = "-|-"; 
    rec_io_set_separator(r, sep, sep + 3);

    const char s3[] = "ciao-|-mamma, come stai?-|-aaa";
    size_t s3_len = sizeof(s3) - 1;

    assert(rec_io_read_record(r, s3, s3 + s3_len) == 3);
    assert(rec_io_write_record(r, buf, 2000, "ciao ciao!") == 10);
    assert(memcmp(buf, "ciao ciao!", 10) == 0);

    fprintf(stderr,"%zu\n",(rec_io_write_record(r, buf, 2000, "%2%1")));
    fprintf(stderr,"%s\n",buf);
    assert(rec_io_write_record(r, buf, 2000, "%2%1") == 20);
    assert(memcmp(buf, "aaamamma, come stai?", 6) == 0);

    sep = "\0\0"; 
     fprintf(stderr,"Im here 79\n");
    rec_io_set_separator(r, sep, sep + 2);
     fprintf(stderr,"Im here 80\n");

      fprintf(stderr,"Im here 83\n");
    const char s4[] = "ciao\0\0mamma, come stai?\0\0aaa";
    size_t s4_len = sizeof(s4) - 1;
 fprintf(stderr,"Im here 85\n");
    assert(rec_io_read_record(r, s4, s4 + s4_len) == 3);
     fprintf(stderr,"Im here 86\n");
    assert(rec_io_write_record(r, buf, 2000, "ciao ciao!") == 10);
    assert(memcmp(buf, "ciao ciao!", 10) == 0);
 fprintf(stderr,"Im here 88\n");
    assert(rec_io_write_record(r, buf, 2000, "%2%1") == 20);
    assert(memcmp(buf, "aaamamma, come stai?", 6) == 0);

    struct rec_io * r2 = rec_io_new();
    assert(r2);

    const char sep2[] = "come";
    rec_io_set_separator(r2, sep2, sep2 + 4);

    assert(rec_io_read_record(r2, s4, s4 + s4_len) == 2);
    fprintf(stderr,"%s\n",buf);
    fprintf(stderr,"%d\n",(rec_io_write_record(r2, buf, 2000, "%1") == 11));
    assert(rec_io_write_record(r2, buf, 2000, "%1") == 11);
    assert(memcmp(buf, " stai?\0\0aaa", 11) == 0);
    assert(rec_io_write_record(r2, buf, 2000, "%0") == 13);
    assert(memcmp(buf, "ciao\0\0mamma, ", 13) == 0);
    assert(rec_io_write_record(r2, buf, 2000, "%1-%0-") == 26);
    assert(memcmp(buf, " stai?\0\0aaa-ciao\0\0mamma, -", 26) == 0);

    const char sep3[] = "\0";
    rec_io_set_separator(r2, sep3, sep3 + 1);

    assert(rec_io_read_record(r2, s4, s4 + s4_len) == 5);
    assert(rec_io_write_record(r2, buf, 2000, "-%1-") == 2);
    assert(memcmp(buf, "--", 2) == 0);
    assert(rec_io_write_record(r2, buf, 2000, "+%1+%3+") == 3);
    assert(memcmp(buf, "+++", 3) == 0);

    rec_io_destroy(r2);
    rec_io_destroy(r);

    return 0;
}
