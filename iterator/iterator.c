#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "iterator.h"

struct iterator{
    char* text;
    char* separator;
    const char* itr;
    int   len;
    int   index;
    const char* active_separator;
};

static char* def = ",;";

struct iterator* create_iterator(){
    struct iterator* res = malloc(sizeof(struct iterator));
    if(!res)return NULL;
    res->text = NULL;
    res->separator = NULL;
    res->itr = NULL;
    res->len = 0;
    res->index = 0;
    res->active_separator = def;
    return res;
}

void destroy_iterator(struct iterator* i){
    if(!i)return ;
    if(i->text)free(i->text);
    if(i->separator)free(i->separator);
    free(i);
}

int set_text(struct iterator* i,const struct sequence* t){
    if(!i)return 0;
    if(!t)return 0;
    if(i->text)free(i->text);

    //deep copy
    int len = t->end - t->begin;
    i->text = malloc(len+1);
    memcpy(i->text,t->begin,len);
    i->text[len] = '\0';

    //set i
    i->itr = i->text;
    i->index = 0;
    i->len = len;
    if(i->separator) i->active_separator = i->separator;
    return 1;
}

int set_separators(struct iterator* i,const struct sequence* s){
    if(!i)return 0;
    if(!s)return 0;
    if(i->separator)free(i->separator);

    //deep copy
    int len = s->end - s->begin;
    i->separator = malloc(len+1);
    memcpy(i->separator,s->begin,len);
    i->separator[len] = '\0';
    i->active_separator = i->separator;
    return 1;
}

int get_next(struct iterator* i,struct sequence* x){
    if(!i)return 0;

    //if has finished 
    //example
    //len = 5,index :0,1,2,3,4
    //index = 4,still need to see this
    //index = 5, overflow
    //so index >= len means in the end
    if(i->index >= i->len)return 0;


    //skip all the separator first
    while(i->index < i->len && strchr(i->active_separator,*(i->itr))){
        i->index ++;
        i->itr ++;
    }

    //check
    if(i->index >= i->len)return 0;



    const char* token_start = i->itr;
    int len = 0;
    while(i->index < i->len){
        
        //current is separator,stop
        if(strchr(i->active_separator,*(i->itr))){
            x->begin = token_start;
            x->end = x->begin + len;
            break;
        }
        //else current is not separator , continue
        else{
            i->index ++;
            i->itr ++;
            len ++;
        }
    }

    //handle orphan
    x->begin = token_start;
    x->end = x->begin + len;
    return 1;
}
