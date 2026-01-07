#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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


static char* mapping[128];
static int has_mapping[128];

void error()
{
    fprintf(stderr,"error");
    exit(EXIT_FAILURE);
}


void get_table()
{
    int c;
    int in_word = 0;
    char* write = NULL;
    c = getchar();
    if(c<128)
    {
        ungetc(c,stdin);
        return;
    }
    ungetc(c,stdin);
    while((c=getchar())!=EOF)
    {
        if(c == '\n')return;
        
        if(in_word == 0)
        {
            //if meet >= 128,then start to write this one
            if(c >= 128)
            {
                in_word = 1;
                if(has_mapping[c-128]==1)
                {
                    error();
                    return;
                }
                mapping[c-128] = malloc(2000);
                write = mapping[c-128];
                has_mapping[c-128] = 1;

                continue;
            }
            else 
            {
                error();
                return;
            }

        }

        else if(in_word == 1)
        {
            if(c>=128)
            {
                *write = '\0';
                if(has_mapping[c-128]==1)
                {
                    error();
                    return;
                }
                mapping[c-128] = malloc(2000);
                write = mapping[c-128];
                has_mapping[c-128] = 1;
                continue;
            }
            else
            {
                if(!isalpha((unsigned char)c))
                {
                    error();
                    return;
                }
                *write ++ = c;
                continue;
            }
        }
    }
    //handle orphan
    if(in_word ==1)
    {
        *write = '\0';
    }
}


void print()
{
    int c;
    while((c=getchar())!=EOF)
    {
        if(c>=128)
        {
            if(has_mapping[c-128]==1)
            {
                printf("%s",mapping[c-128]);
            }
            else
            {
                error();
                return;
            }
        }
        else
        {
            putchar(c);
        }
    }
}




int main(int argc,char* argv[])
{
    get_table();
    print();

}