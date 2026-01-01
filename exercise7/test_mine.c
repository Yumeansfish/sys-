#include<string.h>
#include<stdio.h>
#include<stdlib.h>

static char* saved_ptr = NULL;

char* string_tokenize(char*str,const char* delim){
    if(!str && !*saved_ptr)return NULL;
    if(str){
        saved_ptr = str;
    }
    while(*saved_ptr && strchr(delim,*saved_ptr))saved_ptr++;
    char* start = saved_ptr;
    while(*saved_ptr){
            if(strchr(delim,*saved_ptr)){
                *saved_ptr++ = '\0';
                return start;
            }
            else saved_ptr ++;
        }
    return start;
}

int main(){
    char buffer[100];
    strcpy(buffer, "ab,cd,,");
    printf("Testing: \"%s\"\n\n", buffer);
    
    char* token = string_tokenize(buffer,",");
    int count = 0;
    while(token!=NULL){
        printf("Token %d: \"%s\"\n", ++count, token);
        token = string_tokenize(NULL,",");
    }
    printf("\nTotal tokens: %d\n", count);
    return 0;
}
