#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>
#include "fwd.h"

// Exercise 33. (60’) In a source file called fwd.c write a library that implements a basic forwarding
// table for IPv4. The library must define (i.e., implement) all the declarations in the following header
// file.
// File fwd.h: [download this file]
// #ifndef FWD_H_INCLUDED
// #define FWD_H_INCLUDED
// struct fwd_table;
// /* Constructor: return the null pointer in case of failure. */
// struct fwd_table * fwd_new();
// /* Destructor: clear all memory allocated for the given table. */
// void fwd_delete(struct fwd_table * t);
// /* Associate an IPv4 prefix with an output port in the given table.
// * The prefix is a string of the format IPv4−address/prefix−length.
// * For example, the strings "127.0.0.0/8" and "128.138.196.0/19" are
// * valid prefixes. Return 0 on failure, either because the format of
// * the given prefix is wrong, or because memory is exhausted. Return
// * non−zero on success.
// */
// int fwd_add(struct fwd_table * t, const char * prefix, int port);
// /* Clear the table. */
// void fwd_clear(struct fwd_table * t);
// /* Return the output port for the given IPv4 address. The output port
// * is the one associated with the longest prefix that matches the
// * given address. Return −1 if no such prefix is found or if the
// * format of the given address is wrong.
// */
// int fwd_forward(const struct fwd_table * t, const char * address);
// #endif
// Recall the basics of IPv4 addressing and forwarding. An address is a 32-bit value represented as a
// string a1.a2.a3.a4, where ai are numeric values each corresponding to an unsigned 8-bit decimal
// number, and together they represent the 32-bit address where a1 contains the most significant bits
// and a4 the least significant bits of the address.
// A prefix is an address plus a length. The length is an integer between 0 and 32. An address x
// matches a prefix p/ℓ of length ℓ if and only if the ℓ most significant bits of p are exactly the
// same as the ℓ most significant bits of x. For example, the address 127.0.1.1 matches the prefix
// 127.0.0.0/8, because both the address and the prefix have exactly the same most significant 8 bits,
// namely 127 (base 10) or 11111111 (base 2).
// The forwarding function (fwd_forward) must return the port number associated with the longest
// prefix matching the given address in the given table.
// Hint 1: use sscanf (declared in stdio.h) to read prefixes and addresses from strings.
// Hint 2: you may use the integral types uint8_t and uint32_t declared in stdint.h to represent
// addresses and prefixes. These data types are easy to read as numbers, but then require bit-wise
// operations to perform the matching. As an alternative, you may simply represent addresses as
// 45
// arrays of 32 bits each represented with, say, a character. These are perhaps more straightforward
// for matching, but require a conversion when reading bytes as numbers.



struct fwd_table{
    struct fwd* head;
};

struct fwd{
    uint32_t ip;
    int port;
    int len;
    struct fwd* next;
};


struct fwd_table* fwd_new()
{
    struct fwd_table* new = malloc(sizeof(struct fwd_table));
    if(!new)return NULL;
    new->head = NULL;
    return new;
}

void fwd_delete(struct fwd_table* t)
{
    struct fwd* itr = t->head;
    while(itr)
    {
        struct fwd* tmp = itr->next;
        free(itr);
        itr = tmp;
    }
    free(t);
}

void fwd_clear(struct fwd_table* t)
{
    struct fwd* itr = t->head;
    while(itr)
    {
        struct fwd* tmp = itr->next;
        free(itr);
        itr = tmp;
    }
    t->head = NULL;
}


int tokenizer(char** tokens,char* copy,char* delim)
{
    int count = 0;
    char* token = strtok(copy,delim);
    while(token!=NULL)
    {
        tokens[count++]=token;
        token = strtok(NULL,delim);
    }
    return count;
}

int validate_tokens(char** tokens,int count)
{
    for(int i=0;i<count-1;i++)
    {
        if(strlen(tokens[3])>3)return 0;
    }
    if(count==5)
    {
        int len = atoi(tokens[4]);
        if(len>32 || len<0)return 0;
    }
    return 1;
}



int fwd_add(struct fwd_table*t,const char* prefix,int port)
{
    char* tokens[100];
    char* copy = strdup(prefix);
    if(!copy)return 0;
    int count =tokenizer(tokens,copy,"./");
    if(count!=5)return 0;
    int val = validate_tokens(tokens,count);
    if(!val)return 0;
    int a1 = atoi(tokens[0]);
    int a2 = atoi(tokens[1]);
    int a3 = atoi(tokens[2]);
    int a4 = atoi(tokens[3]);
    int len = atoi(tokens[4]);
    uint32_t ip = (a1<<24)|(a2<<16)|(a3<<8)|a4;
    struct fwd* new = malloc(sizeof(struct fwd));
    if(!new)return 0;
    new->len = len;
    new->ip = ip;
    new->port = port;
    new->next = t->head;
    t->head = new;
    return 1;
}

int fwd_forward(const struct fwd_table*t,const char* address)
{
    char* tokens[100];
    char* copy=strdup(address);
    if(!copy)return 0;
    int count = tokenizer(tokens,copy,".");
    int val = validate_tokens(tokens,count);
    if(!val)return -1;
    int a1= atoi(tokens[0]);
    int a2 = atoi(tokens[1]);
    int a3 = atoi(tokens[2]);
    int a4 = atoi(tokens[3]);
    uint32_t ip = (a1<<24)|(a2<<16)|(a3<<8)|a4;
    struct fwd* itr = t->head;
    int max = 0;
    int res = -1;
    uint32_t mask = 0;
    while(itr)
    {
        mask = 0;
        for(int i =0;i<itr->len;i++)
        {
            mask = mask|(1<<(31-i));
        }
        if((mask&ip) == (mask&itr->ip))
        {
            if(itr->len >= max)
            {
            max = itr->len;
            res = itr->port;
            }
        }      
        itr = itr->next;
    }
    return res;
}