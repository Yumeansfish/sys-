#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ochecker.h"



struct ochecker{
    char* answer;
    char* iterator;
    oc_status_t oc_status;
    int size;
    size_t pos;
    size_t col;
    size_t row;
};

void reset(struct ochecker* oc){
    if(oc->answer)free(oc->answer);
    oc->size = 0;
    oc->pos = 1;
    oc->col=1;
    oc->row=1;
}



struct ochecker* oc_create(){
    struct ochecker* x = malloc(sizeof(struct ochecker));
    if(!x){
        fprintf(stderr,"mem");
        return NULL;
    }
    x->answer = NULL;
    x->iterator = NULL;
    x->oc_status = OC_CLOSED;
    x->size = 0;
    x->pos = 1;
    x->col = 1;
    x->row = 1;
    return x;
}

void oc_destroy(struct ochecker* x){
    if(x->answer)free(x->answer);
    free(x);
}

int oc_open_file(struct ochecker* x,const char* fname){
    reset(x);
    FILE* fp = fopen(fname,"rb");
    if(!fp){
        fprintf(stderr,"cannot open file");
        x->oc_status = OC_CLOSED;
        return 0;
    }
    fseek(fp,0,SEEK_END);
    int len = ftell(fp);
    fseek(fp,0,SEEK_SET);
    x->answer = malloc(len);
    fread(x->answer,1,len,fp);
    x->oc_status = OC_OPEN;
    x->size = len;
    x->iterator = x->answer;
    fclose(fp);
    return 1;
}
    


int oc_open_mem(struct ochecker* x,const char* begin,const char* end){
    int len = end-begin;
    reset(x);
    x->answer = malloc(len);
    if(!x->answer){
        fprintf(stderr,"mem");
        x->oc_status = OC_CLOSED;
        return 0;
    }
    memcpy(x->answer,begin,len);
    x->oc_status = OC_OPEN;
    x->size = len;
    x->iterator = x->answer;
    return 1;
}

int oc_open_str(struct ochecker* x,const char* s){
    reset(x);
    x->answer = strdup(s);
    if(!x->answer)
    {
    fprintf(stderr,"mem");
    x->oc_status = OC_CLOSED;
    return 0;
    }
    x->oc_status = OC_OPEN;
    x->size = strlen(s);
    x->iterator = x->answer;
    return 1;
}


int oc_putc(struct ochecker* oc,char c){
    if(oc->oc_status == OC_CLOSED)return 0;
    if(oc->oc_status == OC_ERROR) return 0;
    //if ==c and not overflow,add pos and iterator
    if(oc->pos <= oc->size && *oc->iterator == c){
        oc->iterator++;
        oc->pos++;
        if(c=='\n'){
            oc->row++;
            oc->col =1;
        }
        else{
            oc->col++;
        }
        return 1;
    }
    //if != c or overflow,error 
    else {
        oc->oc_status = OC_ERROR;
        return 0;
    }
}

int oc_puts(struct ochecker* oc,const char* c){
    while(*c){
        int res = oc_putc(oc,*c);
        if(res)c++;
        else return 0;
    }
    return 1;
}

int oc_write(struct ochecker* oc,const char* buf,size_t len){
    for(size_t i =0;i<len;i++){
        int res = oc_putc(oc,buf[i]);
        if(!res)return 0;
    }
    return 1;

}

int oc_close(struct ochecker* oc){
    if(oc->oc_status == OC_ERROR)return 0;
    if(oc->size != oc->pos-1){
        oc->oc_status = OC_ERROR;
        return 0;
    }
    oc->oc_status = OC_CLOSED;
    return 1;
}


oc_status_t oc_status(const struct ochecker* oc){
    return oc->oc_status;
}

size_t oc_position(const struct ochecker* oc){
    return oc->pos;
}

size_t oc_line(const struct ochecker* oc){
    return oc->row;
}

size_t oc_column(const struct ochecker* oc){
    return oc->col;
}

