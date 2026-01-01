#include<string.h>
#include<stdio.h>
#include<stdlib.h>

static char* saved_ptr = NULL;

char* string_tokenize(char*str,const char* delim){
    if(str){
        saved_ptr = str;
    }
    if(!saved_ptr)return NULL;
    while(*saved_ptr && strchr(delim,*saved_ptr))saved_ptr++;
    if(!*saved_ptr)return NULL;
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
    printf("Test 1: First call with NULL\n");
    char* token = string_tokenize(NULL, ",");
    printf("Result: %s\n\n", token ? token : "NULL");

    printf("Test 2: Normal usage\n");
    char buffer[100];
    strcpy(buffer, "abc");
    saved_ptr = NULL;  // 重置
    token = string_tokenize(buffer, ",");
    printf("Token 1: %s\n", token ? token : "NULL");
    token = string_tokenize(NULL, ",");
    printf("Token 2: %s\n\n", token ? token : "NULL");

    printf("Test 3: Trailing delimiters\n");
    strcpy(buffer, "ab,cd,,");
    saved_ptr = NULL;  // 重置
    int count = 0;
    token = string_tokenize(buffer, ",");
    while(token != NULL){
        printf("Token %d: \"%s\"\n", ++count, token);
        token = string_tokenize(NULL, ",");
    }
    printf("Total: %d tokens\n\n", count);

    printf("Test 4: Leading delimiters\n");
    strcpy(buffer, ",,ab,cd");
    saved_ptr = NULL;  // 重置
    count = 0;
    token = string_tokenize(buffer, ",");
    while(token != NULL){
        printf("Token %d: \"%s\"\n", ++count, token);
        token = string_tokenize(NULL, ",");
    }
    printf("Total: %d tokens\n", count);

    return 0;
}
