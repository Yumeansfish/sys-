#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "rec_io.h"

static char* def_sep = " ";


struct rec_io{
    char* sep; //separator
    int len; //length of separator
    struct sequence* tokens;//tokens part
    int size;//tokens index for next writting position
    int capacity;
};

struct sequence{
    const char* begin;
    const char* end;
};

void tokens_realloc(struct rec_io *r)
{
    int new_capacity = 0;
    if(r->capacity ==0)new_capacity = 100;
    else new_capacity = r->capacity *2;
    r->capacity = new_capacity;
    struct sequence* tmp = realloc(r->tokens,r->capacity*sizeof(struct sequence));
    if(!tmp)return ;
    r->tokens = tmp;
}


extern struct rec_io * rec_io_new()
{
    struct rec_io* new =malloc(sizeof(struct rec_io));
    if(!new)return NULL;
    new->sep = NULL;
    new->len = 0;
    new->size = 0;
    new->tokens = NULL;
    new->capacity = 0;
    return new;
}


void rec_io_destroy(struct rec_io * r)
{
    if(r->sep)free(r->sep);
    if(r->tokens)free(r->tokens);
    free(r);
}


void rec_io_set_separator(struct rec_io * this, const char * begin, const char * end)
{
    if(this->sep)free(this->sep);
    //copy sep into rec io
    size_t len = end - begin;
    if(len>MAX_SEPARATOR_LENGTH)return;
    this->sep = malloc(len+1);
    if(!this->sep)return;//if mem boom
    memcpy(this->sep,begin,len);
    this->sep[len] = '\0';
    this->len = len;
}


int tokenizer(struct rec_io * r,const char* begin,const char* end)
{
    size_t sep_len = 0;
    int res = 0;
    char* sep = NULL;
    if(r->sep) 
    {
        sep = r->sep;
        sep_len = r->len;
    }
    else 
    {
        sep = def_sep;
        sep_len =1;
    }
    

    const char* start = begin;
    while(begin<end)
    {
        if(strncmp(begin,sep,sep_len)==0)
        {
            if(r->size>=r->capacity)tokens_realloc(r);
            r->tokens[r->size].begin = start;
            r->tokens[r->size].end = begin;
            r->size++;
            res++;
            begin+=sep_len;
            start = begin;
        }
        else
        {
            begin++;
        }
    }
    //handle orphan
    if(begin>start)
    {
        if(r->size>=r->capacity)tokens_realloc(r);
        r->tokens[r->size].begin = start;
        r->tokens[r->size].end = begin;
        r->size++;
        res++;
    }
    if(res==0)return res+1;
    return res;
}


int rec_io_read_record(struct rec_io * this, const char * begin, const char * end)
{
    //reset token count
    this -> size = 0;

    //check length
    size_t len = end-begin;
    if(len>MAX_RECORD_LENGTH)return 0;

    
    int res = 0;
    //do tokenize,if has seprator ,pass it otherwise use default separator
    res = tokenizer(this,begin,end);
    return res;
}

size_t rec_io_write_record(struct rec_io * this,
				  char * out, size_t maxlen, const char * format)
{

    //result
    size_t count = 0;

    //read format and write in out
    const char* read = format;
    char* write = out;

    //read loop
    while(*read)
    {
        if(*read == '%')
        {
            //find the target string and write it to out
            int index = *(read+1)-'0';
            //example
            // index = 0, tokencount = 0,not valid
            if(this->size>index)
            {
            const char* begin = this->tokens[index].begin;
            const char* end = this->tokens[index].end;
            while(begin<end)
                {
                    if(count<maxlen)
                    {
                        *write++ = *begin++;
                        count++;
                    }
                    else
                    {
                        *write = '\0';
                        return count;
                    }
                }
            }
            //now read is still in #,+=2
            read+=2;
        }
        //dont have replacement, directly write in out 
        else
        {
            if(count<maxlen)
            {
                *write ++ = *read++;
                count++;
            }
            else
            {
                *write = '\0';
                return count;
            }
        }
    }
    *write = '\0';
    return count;
}

