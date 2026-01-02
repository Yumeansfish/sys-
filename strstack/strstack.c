#include<stdio.h>
#include<stdlib.h>
#include<string.h>


static char* stack = NULL;
static int top = 0;//point to next write position
static int capacity = 0;




void strstack_use_buffer(char * mem,size_t mem_size){
    if(!mem)return;
    stack = mem;
    capacity = mem_size;
}


void strstack_clear(){
    top = 0;

}


//example:
//capacity = 10;
//top = 0;
//len = 9
//top+len = 9
//top = 8 end of this 
//top = 9 '\0'
//top = 10
//its okay

//top = 0
//len = 10
//top + len = 10 
//0-9 for writing len = 10
//10 for writing '\0'
//then top need go to 11 but overflow

//so top + len == capacity need return 0;


int strstack_push(const char* s){
    int len = strlen(s);
    
    //need remain a pos for '\0'
    if(top+len >= capacity)return 0;
    while(*s){
        stack[top++] = *s;
        s++;
    }
    stack[top++] = '\0';
    return 1; 
}

//assume i have hello
//0-4 for maintain hello
//5 for maintain '\0'
//top = 6
//then top --;top = 5
//then top --;top = 4
//enter while loop
//top -- until top = 0
//return &stack[top] = return "hello"

//another situation
//assume i have hello and ciao
//0-4 for hello
//5 for '\0' of hello
//6-9 for ciao
//10 for '\0' of ciao
//top = 11
//top = 10 
//top = 9
//enter while loop
//top -- until top = 5
//then return &stack[top+1] = return "ciao"

//has two consecutive '\0'
//0-4 for hello
//5 '\0'
//6 '\0'
//7-10 for ciao
//11 for '\0'
//top = 12
//top = 11
//top = 10
//enter while loop
//top = 7
//return ciao okay!
//top = 6
//top = 5
//enter while loop! now has issue
//becasue stack[top]== '\0' so it wont enter while loop
//then it will execute return &stack[top+1] but its still '\0'



const char* strstack_pop(){
    if(top==0)return 0;
    top--;//move top to '\0'
    top--;//move to next;
    while(stack[top]&&top>0){
        top--;
    }
    //now top point to '\0' or bottom
    //bottom
    if(top == 0) return &stack[top];

    //'\0'
    else {
        top++;
        return &stack[top];
    }
}