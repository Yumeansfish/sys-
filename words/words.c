#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "words.h"

// Exercise 56. (50’) In a source file called words.c or words.cc write a data structure in C or C++,
// defined by the following declarations, that can represent a sequence of lines of text and that can
// match those lines against a set of strings.
// struct lines;
// struct lines * lines_create();
// void lines_destroy (struct lines * l);
// int add_line (struct lines * l, const char * line);
// int remove_line (struct lines * l, int id);
// int match (struct lines * l, const char * output[], int max_output,
// const char * words);
// lines_create() creates a lines object that initially contains no lines of text. Returns the null pointer
// in case of a memory allocation failure.
// lines_destroy(l) destroys the given lines object, deallocating all its resources.
// add_line(l,line) adds the given line of text to the given object l. Returns a unique identifier for that
// line, or a negative number if memory allocation fails. Notice that the given line object belongs to
// the caller, and therefore its content might change. add_line(l,line) must therefore copy that text in
// an internally managed data structure.
// remove_line(l,id) removes the line with the given id from object l. Returns true when the given id
// is present and then removed, or false when the given id does not exist.
// match(l,output,maxlen,words) takes a lines object l, an array output of char pointers of length
// maxlen, and a string words containing zero or more words separated by spaces. The match func-
// tion must write into the output array a sequence of lines that match the words in words. More
// specifically, a line X matches a set of words w1, w2, . . . if every word wi is a substring of X. Notice
// that wi can appear anywhere in X, and does not have to match a whole word in X. In fact, each
// line in the l object is considered and therefore should be stored as a single string. For example:
// add_line(l, "ciao a tutti " );
// add_line(l, "ciao ciao");
// match(l, output, 100, "ti ia"); /* returns "ciao a tutti" */
// The match function must return lines in the same ordered they were added. If a line X is removed
// and then later an identical line is added, the position of that line in the output must be last. For
// example:
// int id1 = add_line(l, "ciao a tutti " );
// int id2 = add_line(l, "ciao ciao");
// remove_line(l, id1);
// id1 = add_line(l, "ciao a tutti " );
// match(l, output, 100, "ciao"); /* returns "ciao ciao", "ciao a tutti" */
// Notice that the match function must return matching lines by copying pointers to those lines into
// the output array. Those pointers point to data owned by the l object, which must be valid after the
// match call returns and at least until any other call involving object l. No more than maxlen lines
// must be returned. The match function returns the number of lines returned through the output
// vector.



struct lines{
    char* str;
    int id;
    struct lines* next;
};

static int cur_id = 0;




struct lines* lines_create()
{
    struct lines* new =malloc(sizeof(struct lines));
    if(!new)return NULL;
    new->str = NULL;
    new->next = NULL;
    new->id = 0;
    cur_id++;
    return new;
}

void lines_destroy(struct lines* l)
{
    while(l)
    {
        if(l->str)free(l->str);
        struct lines* tmp = l->next;
        free(l);
        l = tmp;
    }
    cur_id = 0;
}


int add_line(struct lines* l,const char* line)
{
    int len = strlen(line);
    struct lines* new = malloc(sizeof(struct lines));
    if(!new)return -1;
    new -> str = malloc(len+1);
    if(!new->str)return -1;
    memcpy(new->str,line,len);
    new->str[len] = '\0';
    new->id = cur_id;

    //tail insert
    while(l->next)l=l->next;
    l->next = new;
    new->next = NULL;
    cur_id++;
    return new->id;
}

int remove_line(struct lines* l,int id)
{
    while(l->next)
    {
        if(l->next->id == id)
        {
            struct lines* tmp = l->next;
            l->next = l->next->next;
            if(tmp->str)free(tmp->str);
            free(tmp);
            return 1;
        }
        else l = l->next;
}
return 0;
}

//check whether str2 is substring of str1
int is_substring(char* str1,char* str2)
{
    while(*str1)
    {
        if(strncmp(str1,str2,strlen(str2))==0)return 1;
        str1++;
    }
    return 0;
}


int match(struct lines* l,const char* output[],int max,const char* words)
{
    char* tokens[1000];
    int size = 0;
    if(strlen(words)==0)return 0;
    char* copy = strdup(words);
    if(!copy)return 0;
    char* token = strtok(copy," ");
    while(token!=NULL)
    {
        // memcpy(tokens[size],token,strlen(token));
        // tokens[size][strlen(token)] = '\0';
        // size++;
        tokens[size++]=token;
        token = strtok(NULL," ");
    }
    struct lines* itr = l->next;
    int count = 0;
    int substr = 1;
    while(itr && count <max)
    {
        substr = 1;
        char* target = itr->str;
        for(int i =0;i<size;i++)
        {
            if(is_substring(target,tokens[i]))continue;
            else 
            {
                substr = 0;
                break;
            }
        }
        if(substr==1)
        {
            output[count++] = itr->str;
            substr = 1;
        }
        itr = itr->next;
    }
    free(copy);
    return count;
}

