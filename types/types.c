#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "types.h"

struct type_system{
    char* name;
    struct type_system* next;//same level
    struct type_system* subtype;
    int ele_count;
};

struct type_system* create(){
    struct type_system* res = malloc(sizeof(struct type_system));
    if(!res)return NULL;
    res->name = NULL;
    res->next = NULL;
    res->subtype = NULL;
    res->ele_count = 0;
    return res;
}

void destroy(struct type_system* ts){
    if(!ts)return;
    destroy(ts->next);
    destroy(ts->subtype);
    if(ts->name)free(ts->name);
    free(ts);
}

struct type_system* find_helper(struct type_system* ts,const char* name){
    if(!ts)return NULL;
    if(!name)return NULL;
    if(ts->name && strcmp(ts->name,name)==0)return ts;
    if(ts->subtype){
            struct type_system* target = find_helper(ts->subtype,name);
            if(target)return target;
        }
    if(ts->next){
            struct type_system* same_level_target = find_helper(ts->next,name);
            if(same_level_target)return same_level_target;
        }
    return NULL;
}


int add_type(struct type_system* ts,const char* type_name,const char* super_name){
    //didnot given type name
    if(!type_name)return TS_BAD_TYPENAME;
    
    //check whether valid typename
    int len = strlen(type_name);
    if(len == 0 || len > MAX_TYPENAME_LEN)return TS_BAD_TYPENAME;

    //give a super name but cannot find
    if(super_name){
        struct type_system* super = find_helper(ts,super_name);
        if(!super)return TS_UNKNOWN_SUPERTYPE;
    }
    //given type name already exist
    struct type_system* sub = find_helper(ts,type_name);
    if(sub)return TS_TYPE_EXISTS;

    struct type_system* new = malloc(sizeof(struct type_system));
    if(!new)return TS_OUT_OF_MEMORY;
    new->name = strdup(type_name);
    if(!new->name){
        free(new);
        return TS_OUT_OF_MEMORY;
    }

    new->ele_count = 0;
    //head insert but super == null
    if(!super_name){
        new->next = ts->subtype;
        ts->subtype = new;
        new->subtype = NULL;
        return TS_SUCCESS;
    }

    //super != NULL
    struct type_system* super = find_helper(ts,super_name);
    new->next = super->subtype;
    super->subtype = new;
    new->subtype = NULL;
    return TS_SUCCESS;
}

int add_element (struct type_system*ts,const char* type_name){
    if(!type_name)return TS_UNKNOWN_TYPE;
    struct type_system* target = find_helper(ts,type_name);
    if(!target)return TS_UNKNOWN_TYPE;
    target->ele_count ++;
    return TS_SUCCESS;
}

int remove_element(struct type_system *ts,const char* type_name){
    if(!type_name)return TS_UNKNOWN_TYPE;
    struct type_system* target = find_helper(ts,type_name);
    if(!target)return TS_UNKNOWN_TYPE;
    if(target->ele_count==0)return TS_NO_ELEMENTS;
    target->ele_count--;
    return TS_SUCCESS;
}

void types_count_helper(struct type_system* ts,int* count){
    if(ts)(*count)++;
    if(ts->subtype)types_count_helper(ts->subtype,count);
    if(ts->next)types_count_helper(ts->next,count);
}



int types_count(struct type_system* ts){
    //ts is sentinel so dont count itself
    struct type_system* target = ts->subtype;
    if(!target)return 0;
    int res = 0;
    types_count_helper(target,&res);
    return res;
}


int is_subtype(struct type_system* ts,const char* subtype,const char* supertype){
    if(!subtype)return TS_UNKNOWN_TYPE;
    if(!supertype)return TS_UNKNOWN_SUPERTYPE;
    struct type_system* super = find_helper(ts,supertype);
    if(!super)return TS_UNKNOWN_SUPERTYPE;
    struct type_system* sub = find_helper(ts,subtype);
    if(!sub)return TS_UNKNOWN_TYPE;
    if(!super->subtype)return TS_FALSE;
    struct type_system* sub_in_super = find_helper(super->subtype,subtype);
    if(!sub_in_super)return TS_FALSE;
    return TS_TRUE;
}

int elements_count (struct type_system * ts, const char * type_name){
    if(!type_name)return TS_UNKNOWN_TYPE;
    struct type_system* target = find_helper(ts,type_name);
    if(!target)return TS_UNKNOWN_TYPE;
    return target->ele_count;
}

void elements_subtype_count_helper(struct type_system*ts,int* count){
    if(ts)(*count)+=ts->ele_count;
    if(ts->subtype)elements_subtype_count_helper(ts->subtype,count);
    if(ts->next)elements_subtype_count_helper(ts->next,count);
}


int elements_subtype_count (struct type_system * ts, const char * type_name){
    if(!type_name)return TS_UNKNOWN_TYPE;
    struct type_system* target = find_helper(ts,type_name);
    if(!target)return TS_UNKNOWN_TYPE;
    if(!target->subtype)return 0;
    int res = 0;
    elements_subtype_count_helper(target->subtype,&res);
    return res;
}






