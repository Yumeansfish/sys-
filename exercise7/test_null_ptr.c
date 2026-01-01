#include<string.h>
#include<stdio.h>
#include<stdlib.h>

static char* saved_ptr = NULL;

char* string_tokenize(char*str,const char* delim){
    if(str){
        saved_ptr = str;
    }
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
    // 测试：第一次调用就传入 NULL
    printf("Test 1: First call with NULL\n");
    char* token = string_tokenize(NULL, ",");
    printf("Result: %s\n\n", token ? token : "NULL");

    // 正常测试
    printf("Test 2: Normal usage\n");
    char buffer[100];
    strcpy(buffer, "abc");
    token = string_tokenize(buffer, ",");
    printf("Token 1: %s\n", token ? token : "NULL");
    token = string_tokenize(NULL, ",");
    printf("Token 2: %s\n", token ? token : "NULL");

    return 0;
}
