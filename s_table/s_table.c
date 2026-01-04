#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "s_table.h"
#define MAX_LEN 100000


// Exercise 31. (120’) Write a library that implements a table of string records. Write a single source
// file called s_table.c or s_table.cc. You may use either C or C++. The library must implement the
// interface functions defined in the s_table.h header file displayed below.
// [download this file]
// #ifndef S_TABLE_H_INCLUDED
// #define S_TABLE_H_INCLUDED
// #include <stddef.h>
// #include <stdio.h>
// struct s_table;
// /* Create and return a new s_table object. Return 0 on failure. */
// struct s_table * s_table_new();
// /* Destroy the given s_table object and release all memory allocated by it. */
// void s_table_delete(struct s_table * t);
// void s_table_clear(struct s_table * t);
// /* Add a record given by the given string
// * Return 0 on failure, 1 on success. */
// int s_table_add_record(struct s_table * t, const char * begin, const char * end);
// /* Remove a record with the given string
// * Return 0 if not found, 1 if found (and removed). */
// int s_table_remove_record(struct s_table * t, const char * begin, const char * end);
// /* Record processor: takes a record and returns an int
// */
// typedef int (*feature_extractor)(const char * begin, const char * end);
// /* Remove all the records that are selected by the given callback
// * function. A record is selected if the selector callback returns an
// * integer value that compares TRUE (i.e., != 0).
// *
// * Return the number of records that were removed. */
// size_t s_table_remove_records(struct s_table * t, feature_extractor selector_callback);
// /* Find a record with the maximal feature extracted by the given
// * callback function. Copies the corresponding record in the given
// * buffer, defined by the record char pointer and the given max buffer
// * length. Never copies more than record_max_len characters.
// *
// * Return the number of characters copied in the record buffer, or 0
// * if there are no records in the table. */
// size_t s_table_max_feature(struct s_table * t, feature_extractor feature_callback,
// char * record, size_t record_max_len);
// /* Print the table on the given FILE stream, one record per line, with
// * the records sorted in increasing order of the feature extracted by
// * the given callback function. */
// void s_table_print_sorted(struct s_table * t, FILE * f,
// feature_extractor feature_callback);
// #endif
// 42
// The library must implement tables of generic records consisting of character strings. The tables
// must support the dynamic addition and removal of records. The library must also support access
// functions controlled by external feature-extraction functions. For example, a table might contain
// the records: “carrots 15Kg CHF 40”, “tomatoes 10Kg CHF 55”, “peppers 2Kg CHF 6”, and the
// user might want to find the most expensive item. To do that, the user would provide a feature-
// extraction function: int get_price(const char * b, const char * e); to parse the record and extract
// the price. The user would then use that function with the library function s_table_max_int_feature.


struct s_table{
    char* str;
    int len;
    struct s_table* next;
};

struct str_feature{
    char* str;
    int feature;
};

static int size = 0;

//use sentinel
struct s_table* s_table_new(){
    struct s_table* new = malloc(sizeof(struct s_table));
    if(!new)return NULL;
    new -> str = NULL;
    new -> len = 0;
    new -> next = NULL;
    return new;
}

void s_table_delete(struct s_table *t){
    while(t){
        if(t->str)free(t->str);
        struct s_table* tmp = t->next;
        free(t);
        t = tmp;
    }
    size = 0;
}

void s_table_clear(struct s_table *t){
    if(t->next)s_table_delete(t->next);
    t->next = NULL;
    size = 0;
}

int s_table_add_record(struct s_table* t,const char* begin,const char* end){
    int len = end - begin;
    struct s_table* new = malloc(sizeof(struct s_table));
    if(!new)return 0;
    new ->str = malloc(len+1);
    memcpy(new->str,begin,len);
    new->str[len] = '\0';
    new->len = len;

    //head insert
    new->next = t->next;
    t->next = new;

    size++;
    return 1;
}

int s_table_remove_record(struct s_table* t,const char* begin,const char* end){
    int len = end - begin;
    char buffer[MAX_LEN];
    memcpy(buffer,begin,len);
    buffer[len] = '\0';

    while(t->next){
        if(strcmp(t->next->str,buffer)==0)
        {
            struct s_table * tmp = t->next;
            t->next = t->next->next;
            if(tmp->str)free(tmp->str);
            free(tmp);
            size--;
            return 1;
        }
        else t = t->next;
    }
    return 0;
}

size_t s_table_remove_records(struct s_table* t,feature_extractor selector_callback)
{
    int count = 0;
    while(t->next)
    {
        if(selector_callback(t->next->str,t->next->str+t->next->len))
        {
            struct s_table* tmp = t->next;
            t->next = t->next->next;
            if(tmp->str)free(tmp->str);
            free(tmp);
            count++;
        }
        else t=t->next;
    }
    size-=count;
    return count;
}

size_t s_table_max_feature(struct s_table * t,
                            feature_extractor feature_callback,
                            char * record,
                            size_t record_max_len)
{
    if(!t->next)return 0;
    int res = 0;//length of copy
    int found =0;//whether found;
    int max = feature_callback(t->next->str,t->next->str+t->next->len);
    while(t->next){
        if(feature_callback(t->next->str,t->next->str+t->next->len)>=max)
        {
            if(t->next->len > record_max_len)
            {
                memcpy(record,t->next->str,record_max_len);
                record[record_max_len] = '\0';
                res = record_max_len;
                found = 1;
            }
            else
            {
                memcpy(record,t->next->str,t->next->len);
                record[t->next->len] = '\0';
                res = t->next->len;
                found = 1;
            }
        }
        t=t->next;
    }
    if(!found)return 0;
    return res;
}    

int compare_func(const void* a,const void* b)
{
    const struct str_feature* sa = (const struct str_feature*)a;
    const struct str_feature* sb = (const struct str_feature*)b;
    return sa->feature - sb->feature;
}



void s_table_print_sorted(struct s_table * t,
                           FILE * f,
                           feature_extractor feature_callback)

{
    struct str_feature arr[size];
    if(!t->next)return;
    int i = 0;
    while(t&&t->next)
    {
        arr[i].str = t->next->str;
        arr[i].feature = feature_callback(t->next->str,t->next->str+t->next->len);
        i++;
        t=t->next;
    }
    qsort(arr,size,sizeof(struct str_feature),compare_func);
    for(int i=0;i<size;i++)
    {
        fprintf(f,"%s\n",arr[i].str);
    }
}
