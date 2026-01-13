#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "tformat.h"

// Exercise 55. (90’) In a source file called tformat.c write a C function declared as follows:
// int t_format(char * t, struct t_opts * opt)
// that formats the given text t, adjusting its spacing in various ways. The spacing is first normalized
// according to these rules:
// • All space characters at the beginning and at the end of a line are removed.
// • Space characters are those for which the standard library function isspace() returns true,
// except that spaces are considered within each line of the text, not across lines. Therefore the
// end-of-line character (’\n’) is not considered a space
// • Empty lines at the beginning and at the end of the text are removed. A line might be empty
// as a result of the removal of space characters.
// • For the remaining space characters, two or more consecutive space characters are replaced
// by a single space character (’ ’).
// For example, the text on left is reformatted as the text on the right:
// These are three spaces, with
// two at the beginning
// These are three spaces, with
// two at the beginning
// In addition to the basic normalization, t_format performs further processing according to some
// formatting options. Notice that every processing is done directly on the text string passed to the
// t_format function. Options are passed through a structure object declared as follows:
// struct t_opts {
// int format_paragraphs;
// int format_punctuation;
// int max_line_len;
// };
// The members of struct t_opts define the following additional formatting operations:
// • If format_paragraphs is non-zero (true), then the text is considered as a sequence of para-
// graphs separated by empty lines. In this case, the paragraph separations are also normalized,
// meaning that consecutive empty lines are replaced by a single empty line. For example, the
// text on left is reformatted as the text on the right:
// This is the
// first paragraph
// This is the second one
// This is the
// first paragraph
// This is the second one
// • If format_punctuation is non-zero (true), then the spacing before some punctuation charac-
// ters are deleted. The punctuation characters are .,;:!? . For example, the text on the left is
// reformatted as the text on the right:
// Nice ! ! ! One , two, three . Nice!!! One, two, three.
// • OPTIONAL: if max_line_len is greater than zero, then paragraphs are formatted into lines
// of at most max_line_len characters. For the purpose of this formatting option, paragraphs
// consist of all the words in groups of consecutive lines separated by empty lines. A word is
// a sequence of non-space characters. If a word is longer than max_line_len, then that word
// 73
// will be placed on a single line by itself. Any other line will have at most max_line_len, also
// counting the spaces that separate words. For example, with max_line_len = 20 the text on
// left is reformatted as the text on the right:
// One two three four five six seven eight nine
// Ten eleven twelve, thirteen, fourteen, fifteen
// One two three four
// five six seven eight
// nine
// Ten eleven twelve,
// thirteen, fourteen,
// fifteen




static char* punctuation = ".,;:!?";

void normalize(char* t)
{
    char* read = t;
    char* write = t;
    int in_word = 0;
    while(*read)
    {
        if(in_word ==0)
        {
            if(isspace(*read)&&*read != '\n')
            {
                read++;
                continue;
            }
            else if(!isspace(*read)&&*read !='\n')
            {
                *write++ = *read++;
                in_word = 1;
                continue;
            }
            else if(*read == '\n')
            {
                if(isspace(*(write-1))&&*(write-1) !='\n')write --;
                *write ++ = '\n';
                read++;
                continue;
            }
        }
        else if(in_word ==1)
        {
            if(!isspace(*read)&&*read !='\n')
            {
                *write++ = *read++;
                continue;
            }
            else if(isspace(*read)&&*read!='\n')
            {
                *write++ = ' ';
                in_word = 0;
                read++;
                continue;
            }
            else if(*read =='\n')
            {
                *write++ ='\n';
                in_word = 0;
                read++;
                continue;
            }
        }
    }
    *write = '\0';
}



void para(char* t)
{
    char* read = t;
    char* write = t;
    int meet_word = 0;
    while(*read)
    {
        if(*read == '\n'&&meet_word == 1)
        {
            *write++ = '\n';
            if(*(read+1)=='\n')*write ++ = '\n';
            while(*read == '\n')read++;
            continue;
        }
        else if(*read == '\n'&& meet_word == 0)
        {
            read++;
            continue;
        }
        else
        {
            meet_word = 1;
            *write ++ = *read++;
            continue;
        }
    }
    int add_n = 0;
    while(*(write-1)=='\n')
    {
        write--;
        add_n = 1;
    }
    if(add_n)*write++ = '\n';
    *write = '\0';
}

void punc(char* t)
{
    char* write = t;
    char* read = t;
    while(*read)
    {
        if(strchr(punctuation,*read))
        {
            while((isspace(*(write-1)) && *(write-1) != '\n'))write--;
            *write++ = *read++;
            continue;
        }
        else 
        {
            *write ++ = *read++;
            continue;
        }
    }
    *write = '\0';
}


void line_len(char* t)
{
    return ;
}



















void t_format(char* t,const struct t_opts* opt)
{
    normalize(t);
    if(opt)
    {
        if(opt->format_paragraphs)para(t);
        if(opt->format_punctuation)punc(t);
        if(opt->max_line_len>0)line_len(t);
    }
}