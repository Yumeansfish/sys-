#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "wcmp.h"


// Exercise 47. (60’) In a source file called wcmp.cc write a C or C++ implementation of the function
// int wcmp(const char * a, const char * b);
// This function takes two C-strings a and b and returns a value that indicates a word-by-word com-
// parison between a and b. A word-by-word comparison considers strings a and b as two, possibly
// empty, sequences of words, Wa = a1, a2, . . . and Wb = b1, b2, . . .. A word is a maximal contiguous
// sequence of alphabetic characters as defined by the standard function isalpha declared in ctype.h.
// So, words are sequences of letters separated by other characters such as spaces, punctuation, and
// numbers. For example, the string "don’t worry" consists of a sequence of three words, namely
// "don", "t", and "worry".
// Thus wcmp(a,b) must return 1, −1, or 0, if the word-by-word comparison between the sequences
// Wa and Wb is greater-than, less-than, or equal, respectively.
// The semantics of a word-by-word comparison between two sequences of words a1, a2, . . . and
// b1, b2, . . . is equivalent to a lexicographical comparison in which we compare pairs of correspond-
// ing words (a1, b1), (a2, b2), . . ., similar to a character-by-character comparison. Each comparison
// of two words is an ordinary lexicographical comparison based on the numeric code of the char-
// acters. So, for example, the sequence (“pasta”, “al”, “pomodoro”) compares greater-than the se-
// quence (“pasta”, “ai”, “funghi”), because the two words in the first position are equal (“pasta”) but
// the two words in the second position compare greater-than, since “al” is lexicographically greater
// than “ai”, because the character ’ l ’ has a numeric code greater than that of character ’ i ’.
// Notice that in a lexicographical comparison, a sequence is always greater than one of its proper
// prefixes. For example: (“pizza”, “margherita”) compares greater-than (“pizza”).


static char** tokens_a = NULL;
static char** tokens_b = NULL;
static int a_size = 0;
static int b_size = 0;
static int a_capacity = 0;
static int b_capacity = 0;


void tokens_a_realloc()
{
    int new_capacity_a = 0;
    if(a_capacity ==0)new_capacity_a = 100;
    else new_capacity_a = a_capacity * 2;
    a_capacity = new_capacity_a;
    char** tmp = realloc(tokens_a,a_capacity*sizeof(char*));
    if(!tmp)return;
    tokens_a = tmp;
}

void tokens_b_realloc()
{
    int new_capacity_b = 0;
    if(b_capacity ==0)new_capacity_b = 100;
    else new_capacity_b = b_capacity * 2;
    b_capacity = new_capacity_b;
    char** tmp = realloc(tokens_b,b_capacity*sizeof(char*));
    if(!tmp)return;
    tokens_b = tmp;
}


int wcmp(const char* a,const char* b)
{
    const char* itr = a;
    const char* start = itr;

    while(*itr)
    {
        if(isalpha((unsigned char)*itr))itr++;
        else
        {
            if(a_size >= a_capacity)tokens_a_realloc();
            int len = itr - start;
            if(len>0)
            {
                tokens_a[a_size] = malloc(len+1);
                memcpy(tokens_a[a_size],start,len);
                tokens_a[a_size][len] = '\0';
                a_size++;
            }
            while(*itr && !isalpha((unsigned char)*itr))itr++;
            start = itr;
        }
    }
    //handle orphan
    if(itr>start)
    {
        if(a_size>=a_capacity)tokens_a_realloc();
        int len = itr-start;
        if(len>0)
        {
            tokens_a[a_size] = malloc(len+1);
            memcpy(tokens_a[a_size],start,len);
            tokens_a[a_size][len] = '\0';
            a_size++;
        }
    }

    itr = b;
    start = itr;

    while(*itr)
    {
        if(isalpha((unsigned char)*itr))itr++;
        else
        {
            if(b_size >= b_capacity)tokens_b_realloc();
            int len = itr - start;
            if(len>0)
            {
                tokens_b[b_size] = malloc(len+1);
                memcpy(tokens_b[b_size],start,len);
                tokens_b[b_size][len] = '\0';
                b_size++;
            }
            while(*itr && !isalpha((unsigned char)*itr))itr++;
            start = itr;
        }
    }
    //handle orphan
    if(itr>start)
    {
        if(b_size>=b_capacity)tokens_b_realloc();
        int len = itr-start;
        if(len>0)
        {
            tokens_b[b_size] = malloc(len+1);
            memcpy(tokens_b[b_size],start,len);
            tokens_b[b_size][len] = '\0';
            b_size++;
        }
    }





    
    if(a_size == 0 &&b_size ==0)return 0;


    int size = 0;
    if(a_size<=b_size)size = a_size;
    else size = b_size;



    //example:
    //size = 5
    //0-4 has toekn

    //start to compare;
    int res = 0;
    for(int i =0;i<size;i++)
    {
        int cur_res = strcmp(tokens_a[i],tokens_b[i]);
        if(cur_res>0)
        {
            res =1;
            break;
        }
        if(cur_res<0)
        {
            res=-1;
            break;
        }
        else continue;
    }
    
    if(res==1)return 1;
    if(res==-1)return -1;
    //when res = 0,need check size;
    if(a_size == b_size)return 0;//real equal
    if(a_size>b_size)return 1;
    // if(a_size<b_size)
    return -1;


  

}

