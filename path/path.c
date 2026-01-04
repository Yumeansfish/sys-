#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include "path.h"

// Exercise 4. (45’) Write a module in a source file called path.c to handle paths (i.e., file names) in
// a Unix file system. The module must implement what you can think of as a class in object-oriented
// programming. The interface of this class is defined in the following header file path.h:
// [download this file]
// #ifndef PATH_H_INCLUDED
// #define PATH_H_INCLUDED
// struct path; /* declaration of the path structure */
// struct path * path_new(const char * name); /* constructor */
// void path_destroy(struct path * path); /* destructor */
// const char * path_append(struct path * this, const char * name);
// const char * path_remove(struct path * this);
// const char * path_value(const struct path * this);
// #endif
// The module supports the construction of a path object with a given initial path, which might be
// a file name, a directory name, or a compound path. A path object must be properly deallocated
// using the destructor. The module uses the Unix directory separator ’/’. The value of a path object
// can be accessed through the value operation.
// The module supports an append operation that adds a file, directory, or path to an existing path. If
// successful, the append operation returns the resulting path. For example, starting from “/usr”, one
// could append “bin” to obtain “/usr/bin”, and then append “emacs” to obtain “/usr/bin/emacs”.
// The module also supports a remove operation that removes the last (rightmost) component of a
// path. If successful, the remove operation returns the resulting path. For example, starting from
// “/usr/bin/emacs”, the resulting path would be “/usr/bin”.
// The module must ensure that a path value is canonical form. A path in canonical form does not
// contain two consecutive directory separators and does not end with a directory separator. So, for
// example “/usr/bin” is a canonical path value, but “/usr/bin/” and “/usr//bin” are not. The user
// may construct or append paths that are not in canonical form, but every path returned by the
// module must be in canonical form.
// Paths must have a fixed maximal length defined by the PATH_MAX macro defined in the limits.h
// header. A append operation that would result in a path exceeding the maximal length must fail by
// returning a null pointer.
// A remove operation that would result in an empty path must fail by returning a null pointer.
// The test_path.c program you find on-line is a test for the path module. Use it to test your imple-
// mentation. In order to get full credit for this exercise, your code must pass the test.



static char* delim = "/";


struct path{
    char** name;
    int size;
    int symbol;
};


void tokenizer(struct path* p,char* copy){
    char* token = strtok(copy,delim);
    while(token!=NULL){
        p->name[p->size++] = strdup(token);
        token = strtok(NULL,delim);
    }
}



struct path* path_new(const char* name){
    struct path* res = malloc(sizeof(struct path));
    if(!res) return NULL;
    res -> symbol = 0;
    res -> size = 0;
    char* copy = strdup(name);
    if(!copy)return NULL;
    res -> name = malloc(sizeof(char*)*PATH_MAX);
    if(!res->name){
        free(copy);
        return NULL;
    }
    tokenizer(res,copy);
    free(copy);
    if(*name == '/')res->symbol = 1;
    return res;
}

void path_destroy(struct path *path){
    if(!path)return;
    if(path->size == 0){
        free(path);
        return;
    }
    for(int i =0;i<path->size;i++){
        free(path->name[i]);
    }
    free(path->name);
    free(path);
    return;
}

const char* path_append(struct path* this,const char* name){
    if(!this || !name)return NULL;
    char* copy = strdup(name);
    if(!copy)return NULL;
    tokenizer(this,copy);
    free(copy);
    return path_value(this);
}

const char* path_remove(struct path* this){
    if(!this)return NULL;
    if(this->size == 0)return NULL;
    if(this->size ==1 && this->symbol ==0)return NULL;
    this->size --;
    return path_value(this);
}


const char* path_value(const struct path* this){
    if(!this)return NULL;
    if(this->size ==0 && this->symbol ==0)return NULL;
    if(this->size ==0 && this->symbol ==1)return "/";

    char* buffer = malloc(PATH_MAX);
    if(!buffer)return NULL;
    char* write = buffer;
    
    
    //handle the first one at first
    if(this->symbol == 1)*write ++ = '/';
    memcpy(write,this->name[0],strlen(this->name[0]));
    write += strlen(this->name[0]);

    //loop
    for(int i =1;i<this->size;i++){
        *write ++ = '/';
        int len = strlen(this->name[i]);
        memcpy(write,this->name[i],len);
        write += len;
    }
    *write = '\0';
    return (const char*) buffer;
}


