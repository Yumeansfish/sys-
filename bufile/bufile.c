#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "bufile.h"

struct bufile{
    char* begin;
    char* end;
};



BUFILE * bufopen(char* begin,char* end)
{
    BUFILE* new = malloc(sizeof(BUFILE));
    if(!new)return NULL;
    new->begin = begin;
    new->end = end;
    return new;
}

void bufclose(BUFILE *buf)
{
    free(buf);
}

char* bufgets(char* s,int size,BUFILE* buf)
{
    if(buf->begin == buf->end)return NULL;
    int count = 0;
    char* read = buf->begin;
    while(buf->begin<buf->end && count< size-1)
    {   
        if(*read == '\n')
        {
            *s++ = '\n';
            *s = '\0';
            read++;
            buf->begin = read;
            return s;
        }
        else 
        {
            *s ++ = *read++;
            buf->begin = read;
            count++;
        }
    }
    *s = '\0';
    return s;
}