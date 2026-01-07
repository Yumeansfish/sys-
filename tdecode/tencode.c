#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


// Exercise 67. (40’) In a source file tdecode.c or tdecode.cc, implement a C or C++ program that
// decodes a file encoded as follows.
// For our purposes, a text file is a file consisting of ASCII characters, meaning bytes between 0 and
// 127 interpreted as characters according to the ASCII code. The lines of a text file are at most
// 1000 characters long. We define a compression encoding for such text files. Since the original
// file (“plaintext”) does not contain bytes between 128 and 255, the idea is to use those byte values
// to represent entire words. A word is a maximal contiguous sequence of lowercase or uppercase
// letters as defined by the isalpha function of the standard library. A code defines which byte maps
// to which word, and vice-versa. In essence, a code consists of byte–word pairs, which are listed at
// the beginning of the encoded file.
// Specifically, if a code exists, the first pair (b1, w1) is stored in the encoded file with b1 as the
// first byte of the file, immediately followed by word w1 in plaintext. A second pair (b2, w2) would
// immediately follow the first one, and so on. The list is terminated by an end-of-line character
// (’\n’). For example, if the code consists of the two pairs (128, hello) and (129, world), then the
// beginning of the encoded file would contain the following bytes:
// 128 104 101 108 108 111 129 119 111 114 108 100 10
// ’h’ ’e’ ’ l ’ ’ l ’ ’o’ ’w’ ’o’ ’r’ ’ l ’ ’d’ ’\n’
// The rest of the encoded file then consists of the plaintext content, except that every word in the
// given code is replaced by the corresponding byte. The example below shows a plaintext file (left-
// hand side) and the corresponding encoded file (right-hand side). In the example, we show bytes
// above 127 as boxed numbers.
// original (“plaintext”) file encoded file
// hello, my friends! 128 hello 129 world
// hello, world!! 128 , my friends!
// hello, world!!! 128 , 129 !!
// 128 , 129 !!!
// Notice that, if the first byte of the encoded file is less than 128 (it is an ASCII character) then that
// means that no code is given. In this case, the encoded file is identical to the plaintext.
// The tdecode program must read the encoded file from standard input and write the decoded
// plaintext file on standard output. In case of error, the program must print an error message on
// standard error, and immediately exit with status EXIT_FAILURE.
// Use the tdecode.tgz test package to test your solution.
// A solution is available here.
// 89
// ▶Exercise 68. (80’) In a source file tencode.c or tencode.cc, implement a C or C++ program that
// encodes a text file using a byte–word code described in Exercise 67. tencode must use a minimal
// code, meaning that the code must produce an encoded file of minimal size compared to other
// codes. Therefore, a word is in the code only when that leads to a reduction of the encoded file.
// Furthermore, since there are only 128 available byte values (from 128 to 255), tencode must priori-
// tize and therefore choose the words that would lead to the maximal size reduction for the encoded
// file.
// In order to define the code, tencode computes the gain of the encoding of a particular word as
// follows. Let lw be the length of word w, and cw be the number of times that w appears in the
// plaintext. Therefore, w uses cw lw bytes of the input, and encoding w with some single byte value
// would use lw + 1 + cw bytes of the output, lw + 1 for the initial mapping plus cw for the content.
// The gain gw of encoding word w is therefore:
// gw = cw lw − lw − 1 − cw
// Thus a valid code includes only words with a positive gain, and among those, the ones with higher
// gains. Specifically, tencode must assign the available code bytes (128–255) to words in decreasing
// order of gain. And to make the encoding deterministic, words that have the same gain must be
// included in the code in alphabetical order.
// The program reads the plaintext from standard input, and writes the encoded file on standard out-
// put. In case of error, the program must print an error message on standard error, and immediately
// exit with status EXIT_FAILURE.
// Hints:
// To define the minimal code, tencode must compute the gain of every word in the file. This means
// that the encoding—where you actually use the code—can start only after you have read the whole
// file. However, since you are reading the file from standard input, you can’t go back to the beginning
// of the file. In practice, this means that you have to store the whole content of the file in memory.
// You must then rank the words by the potential gain of their encoding. This is very easy to do in
// C++. For example, if you store each word together with its gain in a structure:
// struct word_gain {
// std::string word;
// unsigned gain;
// };
// then you can store all potentially useful words in, say, a vector W , and use the standard sort
// function with the desired ordering:
// std::sort (W.begin(), W.end(), wg_less_than);
// where a function bool wg_less_than(const word_gain & a, const word_gain & b) defines the ranking
// criterion. The function is analogous to a less-than comparison, so the function must determine
// whether a precedes b in the desired sorted order



struct word{
    char* str;
    int len;
    int feq;
    int gain;
    int encode;
};



static char* buffer = NULL;
static int size = 0;
static int capacity = 0;
static struct word* table = NULL;
static int table_size = 0;
static int table_capacity = 0;

void error(char* info)
{
    fprintf(stderr,"%s\n",info);
    exit(EXIT_FAILURE);
}



void buffer_realloc()
{
    int new_capacity = 0;
    if(capacity ==0)new_capacity = 100;
    else new_capacity = capacity * 2;
    capacity = new_capacity;
    char* tmp = realloc(buffer,capacity*sizeof(char));
    if(!tmp)error("mem");
    buffer= tmp;
}


void table_realloc()
{
    int new_capacity = 0;
    if(table_capacity ==0)new_capacity = 100;
    else new_capacity = table_capacity * 2;
    table_capacity = new_capacity;
    struct word* tmp = realloc(table,table_capacity*sizeof(struct word));
    if(!tmp)error("mem");
    table = tmp;
}



void write_in_buffer()
{
    int c;
    if(size>=capacity)buffer_realloc();
    while((c=getchar())!=EOF)
    {
        if(size>=capacity)buffer_realloc();
        buffer[size++] = c;
        continue;
    }
}


struct word* find_helper(char* str)
{
    for(int i =0;i<table_size;i++)
    {
        if(strcmp(table[i].str,str)==0)return &table[i];
    }
    return NULL;
}


void add_word(char* start,char* end)
{
    if(table_size>=table_capacity)table_realloc();
    int len = end - start;
    char buffer[len+1];
    memcpy(buffer,start,len);
    buffer[len] = '\0';
    struct word* target = find_helper(buffer);
    //if already has,add feq
    if(target)
    {
        target->feq++;
    }
    //cannot find ,add new
    else if(!target)
    {
        table[table_size].str = malloc(len+1);
        memcpy(table[table_size].str,start,len);
        table[table_size].str[len] = '\0';
        table[table_size].feq = 1;
        table[table_size].len = len;
        table_size++;
    }
}



void get_table()
{
    char* read = buffer;
    int in_word = 0;
    char* start = NULL;
    while(*read)
    {
        if(in_word == 0)
        {
            if(!isalpha(*read))
            {
                read++;
                continue;
            }
            else if(isalpha(*read))
            {
                start =read;
                in_word =1;
                read++;
                continue;
            }
        }
        else if(in_word ==1)
        {
            if(!isalpha(*read))
            {
                add_word(start,read);
                in_word =0;
                read++;
                continue;
            }
            else if(isalpha(*read))
            {
                read++;
                continue;
            }
        }
    }
    //handle orphan
    if(in_word ==1 && read > start)
    {
        add_word(start,read);
    }
}


void calculate_gain()
{
    for(int i =0;i<table_size;i++)
    {
        table[i].gain = table[i].len*table[i].feq-table[i].len-1-table[i].feq;
    }
}

void calculate_encode()
{
    for(int i=0;i<table_size;i++)
    {
        if(table[i].gain>0 &&i<=127)table[i].encode = 1; 
    }
}

int compare_func(const void* a,const void* b)
{
    const struct word* wa = (const struct word*)a;
    const struct word* wb = (const struct word*)b;
    if(wa->gain!=wb->gain)return wb->gain - wa->gain;
    return strcmp(wa->str,wb->str);
}

int find_idx_helper(char* str)
{
    for(int i =0;i<table_size;i++)
    {
        if(strcmp(str,table[i].str)==0)return i;
    }
    return -1;
}


void print_what(char* start,char* end)
{
    char buffer[1000];
    int len = end - start;
    memcpy(buffer,start,len);
    buffer[len] = '\0';
    struct word* target = find_helper(buffer);
    if(target->encode==1)
    {
        int index = find_idx_helper(buffer);
        putchar(128+index);
    }
    else
    {
        printf("%s",buffer);
    }
}


void print()
{
    char* read = buffer;
    int in_word = 0;
    char* start = NULL;
    while(*read)
    {
        if(in_word==0)
        {
            if(isalpha(*read))
            {
                start = read;
                in_word =1;
                read++;
                continue;
            }
            else if(!isalpha(*read))
            {
                putchar(*read);
                read++;
                continue;
            }
        }
        else if(in_word==1)
        {
            if(!isalpha(*read))
            {
                in_word = 0;
                print_what(start,read);
                putchar(*read);
                read++;
                continue;
            }
            else if(isalpha(*read))
            {
                read++;
                continue;
            }
        }
    }
    //handle orphan
    if(in_word ==1 && read>start)
    {
        print_what(start,read);
    }
}

void print_table()
{
    int has_code = 0;
    for(int i =0;i<table_size;i++)
    {
        if(table[i].encode ==1)
        {
            has_code = 1;
            putchar(128+i);
            printf("%s",table[i].str);
        }
    }
    if(has_code)
    putchar('\n');
}



int main(int argc,char* argv[])
{
    write_in_buffer();
    get_table();
    calculate_gain();
    qsort(table,table_size,sizeof(struct word),compare_func);
    calculate_encode();
    print_table();
    print();
}