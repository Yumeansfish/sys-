#include<stdio.h>
#include<string.h>
#include "strqueue.h"

static char* queue = NULL;
static int front =0;
static int back = 0;
static int capacity = 0;
static int size = 0;
static char buffer[1000];

// Exercise 7. (40’) Write a module in a source file called strqueue.c that implements a queue of
// strings (zero-terminated arrays of characters) as defined by the operations declared in the following
// header file strqueue.h:
// [download this file]
// #ifndef STRQUEUE_H_INCLUDED
// #define STRQUEUE_H_INCLUDED
// #include <stddef.h> /* declares size_t */
// extern void strqueue_use_buffer(char * mem, size_t mem_size);
// extern void strqueue_clear();
// extern int strqueue_enqueue(const char * s);
// extern const char * strqueue_dequeue();
// #endif
// The strqueue module must not allocate memory to hold the queue of strings. Instead, that memory
// is provided by the application through the strqueue_use_buffer function. The module may of
// course use other internal meta-data variables.
// The queue supports the following three operations:
// • strqueue_clear initializes the queue, resulting in an empty queue.
// • strqueue_enqueue adds a given string to the queue, returning 1 if successful, or 0 in case
// there is no space to fit that string in the queue. Notice that it would be incorrect to return 0
// when enough space is available.
// • strqueue_dequeue extracts and returns the first string from the queue, returning that string
// (char pointer) or 0 if the queue is empty. The returned string must be valid only until the
// next call to any one of the functions of the strqueue module.
// The test_strqueue.c program you find on-line system is a test for the strqueue module. Use it to
// test your implementation. In order to get full credit for this exercise, your code must pass the test.
// Use the strqueue.tgz test package to test your solution

void strqueue_use_buffer(char* mem,size_t mem_size){
    queue = mem;
    capacity = mem_size;
}

void strqueue_clear(){
    size = 0;
    front = 0;//point to start of the first string
    back = 0;//point to next position for writing
}

int strqueue_enqueue(const char* s){
    int len = strlen(s);
    if(size+len+1 >= capacity)return 0;
    
    while(*s){
        //write in back at first
        queue[back] = *s++;
        //calculate next back
        back = (back+1)%capacity;
    }
    queue[back] = '\0';
    //calculate next position for writing
    back = (back+1)%capacity;
    size += (len + 1);
    return 1;
}


const char* strqueue_dequeue(){
    if(size ==0 )return 0;
    int len= 0;
    char* write = buffer;
    while(queue[front]){
        //write in buffer
        *write ++ = queue[front];
        len++;
        //calculate next front
        front = (front+1)%capacity;
    }
    //when loop end it means front is on '\0'
    front = (front+1)%capacity;
    *write = '\0';
    size -= (len+1);
    return buffer;
}
