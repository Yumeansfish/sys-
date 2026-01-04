#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "rec_io.h"


// Exercise 20. (60’) Write a module that implements a formatting filter for text records. In essence,
// an application uses a filter by first passing a string of characters representing a record, and then by
// producing an output of that input record according to a format string. A text record consists of one
// or more textual fields separated by a separator string. The module must implement filter objects
// as specified by the attached header file rec_io.h (below). An application might create multiple filter
// objects, which may be used at the same time, and that must be independent of each other.
// The test_rec_io1.c program you find on-line is a test for the rec_io module. Use it to test your
// implementation.
// File rec_io.h: [download this file]
// #ifndef REC_IO_H_INCLUDED
// #define REC_IO_H_INCLUDED
// #include <stddef.h>
// struct rec_io;
// /* This is the maximal size for an input record. The module must
// * support input records up to this size.
// */
// #define MAX_RECORD_LENGTH 1000
// /* This is the maximal size for a record separator. The module must
// * support separators up to this size.
// */
// #define MAX_SEPARATOR_LENGTH 10
// /* Constructor
// *
// * Returns a pointer to a valid rec_io object, or NULL in case of
// * error (e.g ., insufficient memory)
// */
// extern struct rec_io * rec_io_new();
// /* Destructor
// */
// extern void rec_io_destroy(struct rec_io *);
// /* Configure this rec_io filter to use the separator string defined by
// * the begin and end pointers. Notice that a separator can be any
// * sequence of bytes (at most MAX_SEPARATOR_LENGTH). In particular, a
// * separator may contain the NULL character (’\0’, one or more).
// *
// * The default separator is the sequence consisting of a single space
// * character. Setting a separator determines how the filter reads any
// * successive input record (with rec_io_read_record).
// */
// extern void rec_io_set_separator(struct rec_io * this, const char * begin, const char * end);
// /* Passes an input record to this filter for later processing by the
// * filter . An input record is any sequence of characters (at most
// * MAX_RECORD_LENGTH) composed of fields separaterd by separator
// * strings. The beginning of the sequence and the end of the sequence
// * are implicit separators, so an input sequence that does not contain
// 26
// * the separator consists of exactly one field equal to the entire
// * sequence. Fields may be zero−length sequences.
// *
// * This method must return the number of fields read.
// */
// extern int rec_io_read_record(struct rec_io * this, const char * begin, const char * end);
// /* Outputs the input record previously read with rec_io_read_record
// * using the given format string. The output is given as a sequence
// * of characters written in the output buffer provided by the
// * application. This method may not write more than maxlen characters
// * into the output buffer. The return value is the actual number of
// * characters written into the output.
// *
// * The format string is a C string, meaning it is terminated by ’\0’.
// * The format string may contain field indicator consisting of a
// * single percent character (’%’) followed by a decimal number.
// * Fields are numbered starting from 0. So, for example, the format
// * string "%0" should output the first fields. A field indicator that
// * points to a field that was not read must have no output (for
// * example, "%4" when only four or less fields were read).
// *
// * Any other character or sequence of characters in the format string
// * must be copied identically into the output. So, for example, the
// * format string "1: %0\n2: %1\n" should output two lines containing
// * the first and second field, respectively.
// *
// * This method can be called multiple times for the same record,
// * possibly with different format strings.
// */
// extern size_t rec_io_write_record(struct rec_io * this,
// char * out, size_t maxlen, const char * format);
// #endif



static char* def = " ";

struct rec_io{
    char* text;
    char* separator;
    int size;
    int index;
    char* itr;
    int len;
};


struct rec_io* rec_io_new(){
    struct rec_io* new = malloc(sizeof(struct rec_io));
    if(!new)return NULL;
    new -> text = NULL;
    new -> separator = def;
    new -> size = 0;
    new -> index = 0;
    new -> itr = NULL;
    new -> len = 1;
    return new;
}

void rec_io_destroy(struct rec_io* i){
    if(!i)return ;
    if(i->text)free(i->text);
    free(i);
}



static char tokens[1000][1000];
static int tokens_len[1000];

void rec_io_set_separator(struct rec_io *this,const char* begin,const char* end){
    if(!this)return;
    int len = end - begin;
    if(len == 0 ||len > MAX_SEPARATOR_LENGTH)return;
    if(this->separator){
        if(this->separator!=def)free(this->separator);
    }
    this->len = len;
    this->separator = malloc(len+1);
    memcpy(this->separator,begin,len);
    this->separator[len] = '\0';
}

int tokenizer(struct rec_io* this){
    int count = 0;
    char* start = this->itr;
    int len = this->len;
    while(this->index <this->size){
        if(this->index+len <this->size &&strncmp(this->separator,this->itr,len)==0){
            memcpy(tokens[count],start,this->itr-start);
            tokens[count][this->itr-start] = '\0';
            tokens_len[count] = this->itr-start;
            count +=1;
            this->itr+=len;
            this->index+=len;
            start = this->itr;
        }
        else{
            this->itr++;
            this->index++;
        }
    }
    //handle orphan
    memcpy(tokens[count],start,this->itr-start);
    tokens[count][this->itr-start] = '\0';
    tokens_len[count] = this->itr-start;
    return (count+1);
}


int rec_io_read_record(struct rec_io* this,const char* begin,const char* end){
    if(!this)return -1;
    int len = end - begin;
    if(len > MAX_RECORD_LENGTH)return -1;
    if(len == 0){
        this -> text = "";
        return 0;
    }
    this->text = malloc(len+1);
    memcpy(this->text,begin,len);
    this->text[len] = '\0';
    this->index = 0;
    this-> size = len ;
    this->itr = this->text;
    int count = tokenizer(this);
    return count;
}


size_t rec_io_write_record(struct rec_io *this,char*out,size_t maxlen,const char* format){
    char* write = out;
    int count = 0;
    while(*format){
        //need copy token to replace %number
        if(*format == '%'){
            const char* start = format;
            format++;
            while(isdigit((unsigned char)*format)){
                format++;
            }
            //now format point to position which is not number
            const char* start_of_number = start +1;
            int num_len = format-start_of_number;
            //open a buffer store the index
            char buffer[10];
            memcpy(buffer,start_of_number,num_len);
            buffer[num_len] = '\0';

            //find it in tokens
            int index = atoi(buffer);
            char* token = tokens[index];
            int token_len = tokens_len[index];

            //format this token to out
            if(count + token_len >= maxlen){
                return count;
            }
            memcpy(write,token,token_len);
            write += token_len;    
            count += token_len;  
        }
        //else
        else{
            if(count+1 >= maxlen){
                return count;
            }
            *write ++ = *format++;
            count ++;
        }

    }
    *write = '\0';
    return count;
}