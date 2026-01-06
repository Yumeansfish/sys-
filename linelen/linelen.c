#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Exercise 49. (40’) In a source file called linelen.c write a C program that reads lines from the
// standard input, and writes on the standard output the lines that are between a minimum and
// maximum length min ≤ ℓ ≤ max. A “line” is a maximal sequence of characters (bytes) terminated
// by the new-line character (‘\n’). This means that the program must not print anything past the last
// new-line character in the input.
// The minimum length min and the maximum length max are passed to the program as non-negative
// decimal numbers as the optional first and second command-line arguments, respectively. By de-
// fault, the minimum length is min = 0 and the maximum length is max = ∞. For example, the
// command “linelen 10 100” must print all the input lines whose length is between 10 and 100
// characters. Instead, the command “linelen 20” must print all the input lines whose length is at
// least 20 characters. And the simple command “linelen” must print all lines.
// When printing a line, regardless of its length, the program must truncate the output to at most 60
// characters. If the line is longer than 60 characters, then the program must add three dots at the
// end of the first 60 characters. For example, in printing the following input lines:
// 0---------1---------2---------3---------4---------5
// 0---------1---------2---------3---------4---------5---------6
// 0---------1---------2---------3---------4---------5---------6---------7
// the program must output
// 0---------1---------2---------3---------4---------5
// 0---------1---------2---------3---------4---------5---------6
// 0---------1---------2---------3---------4---------5---------6...
// Notice that the selection of which lines to print is made on the length of the input, not the length
// of the truncated output. For example, linelen 2000 must print all input lines of 2000 or more
// characters, but it must print only the first 60 characters of each line.


int check_has_n(char* line)
{
    while(*line)line++;
    if(*(line-1)=='\n')return 1;
    return 0;
}


void print(int min,int max)
{
    char line[10000];
    while(fgets(line,sizeof(line),stdin))
    {
        char print_line[61];
        int len;
        if(check_has_n(line))len = strlen(line)-1;
        else continue;

        //no min no max
        if(min==-1&&max==-1)
        {
            if(len>60)
            {
                memcpy(print_line,line,60);
                print_line[60] = '\0';
                if(check_has_n(print_line))
                printf("%s...",print_line);
                else
                printf("%s...\n",print_line);
            }
            else 
            {
                memcpy(print_line,line,len);
                print_line[len] = '\0';
                if(check_has_n(print_line))
                printf("%s",print_line);
                else
                printf("%s\n",print_line);
            }
        }

        else if(max == -1 && min != -1)
        {
            if(len<min)continue;
            if(len>60)
            {
                memcpy(print_line,line,60);
                print_line[60] = '\0';
                if(check_has_n(print_line))
                printf("%s...",print_line);
                else
                printf("%s...\n",print_line);
            }
            else 
            {
                memcpy(print_line,line,len);
                print_line[len] = '\0';
                if(check_has_n(print_line))
                printf("%s",print_line);
                else
                printf("%s\n",print_line);
            }
        }
        else if(max != -1 && min !=-1)
        {
            if(len<min||len>max)continue;
            if(len>60)
            {
                memcpy(print_line,line,60);
                print_line[60] = '\0';
                if(check_has_n(print_line))
                printf("%s...",print_line);
                else
                printf("%s...\n",print_line);
            }
            else 
            {
                memcpy(print_line,line,len);
                print_line[len] = '\0';
                if(check_has_n(print_line))
                printf("%s",print_line);
                else
                printf("%s\n",print_line);
            }
        }

    }
}




int main(int argc,char* argv[])
{
    if(argc == 1)
    {
        print(-1,-1);
    }
    else if(argc >1&&argv[2])
    {
        print(atoi(argv[1]),atoi(argv[2]));
    }
    else print(atoi(argv[1]),-1);
}