#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ochecker.h"


struct ochecker{
    int state;
    int pos;
    int row;
    int col;
    char* itr;
    char* str;
    int size;
    int capacity;
};



struct ochecker* oc_create()
{
    struct ochecker* new= malloc(sizeof(struct ochecker));
    if(!new)return NULL;
    new->state = OC_CLOSED;
    new->pos = 1;
    new->row = 1;
    new->col = 1;
    new->itr = NULL;
    new->str = NULL;
    new->size = 0;
    new->capacity = 0;
    return new;
}

void oc_realloc(struct ochecker* oc)
{
    int new_capacity= 0;
    if(oc->capacity==0)new_capacity = 100;
    else new_capacity = oc->capacity*2;
    oc->capacity = new_capacity;
    char* tmp = realloc(oc->str,oc->capacity*sizeof(char));
    if(!tmp)exit(EXIT_FAILURE);
    oc->str = tmp;
}

void oc_destroy(struct ochecker* oc)
{
    if(oc->str)
    {
        free(oc->str);
        oc->str = NULL;
    }
    free(oc);
    oc=NULL;
}

void reset(struct ochecker* oc)
{
    if(oc->str)free(oc->str);
    oc->itr = NULL;
    oc->pos = 1;
    oc->size = 0;
    oc->row = 1;
    oc->col =1;
    oc->capacity = 0;
    oc->str = NULL;
}



int oc_open_file(struct ochecker* oc,const char* name)
{
    FILE* fp = fopen(name,"r");
    if(!fp)
    {
        oc->state = OC_CLOSED;
        return 0 ;
    }
    reset(oc);
    int c;
    int process = 0;
    while((c=fgetc(fp))!=EOF)
    {
        if(oc->size>=oc->capacity)oc_realloc(oc);
        oc->str[oc->size++] = c;
        process = 1;
        continue;
    }
    if(process)
    {oc->str[oc->size] = '\0';
    oc->state = OC_OPEN;
    oc->itr = oc->str;
    }
    else
    {
        oc->str = malloc(1);
        oc->str[oc->size++]='\0';
        oc->state = OC_OPEN;
        oc->itr = oc->str;
    }
    return 1;
}

int  oc_open_mem(struct ochecker*oc,const char* begin,const char* end)
{
    int len = end-begin;
    reset(oc);
    oc->str = malloc(len+1);
    if(!oc->str)
    {
        oc->state = OC_CLOSED;
        return 0;
    }
    memcpy(oc->str,begin,len);
    oc->str[len] = '\0';
    oc->size += len;
    oc->state = OC_OPEN;
    oc->itr = oc->str;
    return 1;
}

int oc_open_str(struct ochecker*oc,const char* str)
{
    int len = strlen(str);
    reset(oc);
    oc->str = malloc(len+1);
    if(!oc->str)
    {
        oc->state = OC_CLOSED;
        return 0;
    }
    memcpy(oc->str,str,len);
    oc->str[len] = '\0';
    oc->size += len;
    oc->state = OC_OPEN;
    oc->itr = oc->str;
    return 1;
}

size_t oc_position(const struct ochecker* oc)
{
    return oc->pos;
}

size_t oc_line(const struct ochecker* oc)
{
    return oc->row;
}

size_t oc_column(const struct ochecker* oc)
{
    return oc->col;
}

oc_status_t oc_status(const struct ochecker* oc)
{
    return oc->state;
}




int oc_putc(struct ochecker* oc,char c)
{
    if(oc->state == OC_CLOSED||oc->state == OC_ERROR)return 0;
    if(oc->pos > oc->size)
    {
        oc->state = OC_ERROR;
        return 0;
    }
    if(*oc->itr!=c)
    {
        oc->state = OC_ERROR;
        return 0;
    }
    if(*oc->itr==c)
    {
        oc->pos++;
        oc->itr++;
        if(c=='\n')
        {
            oc->row++;
            oc->col = 1;
        }
        else
        {
            oc->col++;
        }
    }
    return 1;
}

int oc_puts(struct ochecker*oc,const char* s)
{
    if(oc->state == OC_CLOSED||oc->state == OC_ERROR)return 0;
    while(*s)
    {
        int res = oc_putc(oc,*s);
        if(res)s++;
        else
        {
            return 0;
        }
    }
    return 1;
}

int oc_write(struct ochecker* oc,const char* buf,size_t len)
{
    if(oc->state == OC_CLOSED||oc->state == OC_ERROR)return 0;
    while(len>0)
    {
        int res = oc_putc(oc,*buf);
        if(res)
        {
            buf++;
            len --;
        }
        else 
        {
            return 0;
        }
    }
    return 1;
}

int oc_close(struct ochecker* oc)
{
    if(oc->state == OC_CLOSED||oc->state == OC_ERROR)return 0;
    if(!*(oc->itr))
    {
        oc->state = OC_CLOSED;
        return 1;
    }
    else
    {
        oc->state = OC_ERROR;
        return 0;
    }
    return 1;
}





