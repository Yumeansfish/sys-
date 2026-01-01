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
    char buffer[100];
    strcpy(buffer, "ab,cd,,");
    printf("Testing: \"%s\"\n", buffer);

    char* token = string_tokenize(buffer,",");
    int count = 0;
    while(token!=NULL){
        printf("Token %d: \"%s\"\n", ++count, token);
        token = string_tokenize(NULL,",");
    }
    printf("Total tokens: %d\n\n", count);

    // 测试开头有分隔符
    strcpy(buffer, ",,ab,cd");
    printf("Testing: \"%s\"\n", buffer);
    saved_ptr = NULL;  // 重置
    token = string_tokenize(buffer,",");
    count = 0;
    while(token!=NULL){
        printf("Token %d: \"%s\"\n", ++count, token);
        token = string_tokenize(NULL,",");
    }
    printf("Total tokens: %d\n", count);

    return 0;
}
