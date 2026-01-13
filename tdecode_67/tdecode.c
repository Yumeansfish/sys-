#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

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
    c=getchar();
    if(c<128)
    {
        ungetc(c,stdin);
        return;
    }
    ungetc(c,stdin);
    int in_word = 0;
    char* write = NULL;
    while((c=getchar())!=EOF)
    {
        if(in_word == 0)
        {
            if(c>=128)
            {
                int index = c-128;
                mapping[index] = malloc(1000);
                has_mapping[index] =1;
                write = mapping[index];
                continue;
            }
            else if(isalpha((unsigned char)c))
            {
                in_word = 1;
                *write++ = c;
                continue;
            }
            else error();
        }
        else if(in_word == 1)
        {
            if(isalpha((unsigned char)c))
            {
                *write ++ = c;
                continue;
            }
            else if(c>=128)
            {
                *write = '\0';
                int index = c-128;
                if(has_mapping[index])
                {
                    error();
                    return;
                }
                mapping[index] = malloc(1000);
                has_mapping[index] = 1;
                write = mapping[index];
                in_word = 0;
                continue;
            }
            else if(c=='\n')break;
            else error();
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
            if(!has_mapping[c-128])
            {
                error();
                return;
            }
            printf("%s",mapping[c-128]);
            continue;
        }
        else 
        {
            putchar(c);
            continue;
        }
    }
}

 

int main(int argc,char* argv[])
{
    get_table();
    print();
}