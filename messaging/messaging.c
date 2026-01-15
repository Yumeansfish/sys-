#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "messaging.h"

// Exercise 34. (80’) In a source file called messaging.cc write a library that implements a simple
// publish/subscribe messaging system. You may write the library in C or C++. The library must
// define (i.e., implement) all the declarations in the following header file.
// File messaging.h: [download this file]
// #ifndef MESSAGING_H_INCLUDED
// #define MESSAGING_H_INCLUDED
// struct server;
// struct server * server_new(); /* return 0 on failure */
// void server_delete(struct server * s);
// struct receiver {
// void (*deliver)(struct receiver * r, const char * message);
// };
// /* return 0 on failure */
// int add_interest(struct server * srv, struct receiver * r, const char * interest);
// void remove_interest(struct server * srv, struct receiver * r, const char * interest);
// void clear_receiver(struct server * srv, struct receiver * r);
// void clear_all(struct server * srv);
// void send(const struct server * srv, const char * message);
// #endif
// A messaging server records the interests of receivers, and then delivers messages according to
// those interests. The server processes messages for delivery through the send function. A message
// is simply a C string (zero-terminated).
// A receiver is an object with a deliver function that the server invokes to deliver messages to that
// receiver. Notice that two distinct receiver objects may use the same deliver function.
// A receiver can be associated with an interest through the add_interest function. The function takes
// a pointer to the receiver object together with an interest string. In this first exercise, an interest is
// a single tag. Exercise 35 extends the notion of an interest to a set of tags. Feel free to implement
// that extension directly.
// A tag is a maximal sequence of alphabetic characters possibly starting with one pound or at char-
// acter (‘#’ or ‘@’). For example, “ciao”, “@mamma”, and “#bellaciao” are valid tags. An interest (a
// tag) matches a message whenever the message contains one or more tags equal to the interest.
// The tags contained in a message are separated by non-tag characters. For example, the message
// “Ciao @mamma, come stai?” contains tags “Ciao”, “@mamma”, “come”, and “stai”, and therefore
// matches the interest “@mamma”. However, the message “Ciao mamma” does not match that same
// interest. The message “Ciao @mammamia” also does not match the interest “@mamma”.
// The send function takes a server and a message, and delivers that message to all the receivers
// that added one or more interest matching the message. In particular, if server s has an interests t
// associated with receiver r , then a call send(s ,m) on server s and a message m matching interest
// t—meaning that m contains t—results in the invocation of the delivery function of r with r and
// m as parameters, that is, r −>deliver(r ,m).
// The remove_interest(s ,r ,t ) function removes the association between receiver r and interest t
// within server s; clear_receiver(s ,r ) removes all the interests associated with receiver r within
// server s; and clear_all (s ) removes all the interests within server s.



struct server{
    struct connection * head;
};

struct connection{
    struct receiver* r;
    char* inter;
    struct connection* next;
};


struct server * server_new(){
    struct server* new = malloc(sizeof(struct server));
    if(!new)return 0;
    new->head=NULL;
    return new;
}



void server_delete(struct server * s){
    struct connection* itr = s->head;
    while(itr)
    {
        if(itr->inter)free(itr->inter);
        struct connection* tmp = itr->next;
        free(itr);
        itr = tmp;
    }
    free(s);
}


int add_interest(struct server * srv, struct receiver * r, const char * interest){
    struct connection* new = malloc(sizeof(struct connection));
    if(!new)return 0;
    new->r = r;
    int len = strlen(interest);
    new->inter = malloc(len+1);
    if(!new->inter)return 0;
    memcpy(new->inter,interest,len);
    new->inter[len] = '\0';
    new->next = srv->head;
    srv->head = new;
    return 1;
}


void remove_interest(struct server * srv, struct receiver * r, const char * interest){
    struct connection dummy = {NULL,NULL,srv->head};
    struct connection* itr = &dummy;
    while(itr->next)
    {
        if(itr->next->r == r&& itr->next->inter &&strcmp(itr->next->inter,interest)==0)
        {
            struct connection* tmp = itr->next;
            itr->next = itr->next->next;
            free(tmp->inter);
            free(tmp);
            srv->head = dummy.next;
            return ;
        }
        itr = itr ->next;
    }
}

void clear_receiver(struct server * srv, struct receiver * r){
    struct connection* itr = srv->head;
    while(itr)
    {
        if(itr->r == r)
        {
            if(itr->inter)
            {
                free(itr->inter);
                itr->inter = NULL;
            }
        }
        itr = itr->next;
    }
}


void clear_all(struct server * srv){
    struct connection* itr = srv->head;
    while(itr)
    {
        if(itr->inter)free(itr->inter);
        struct connection* tmp = itr->next;
        free(itr);
        itr = tmp;
    }
    srv->head= NULL;
}

int is_tag(char ch)
{
    if(isalpha(ch) || ch =='@' || ch=='#')return 1;
    return 0;
}

int find_helper(struct receiver* table[1000],struct receiver* r,int count)
{
    for(int i=0;i<count;i++)
    {
        if(table[i] == r)return 1;
    }
    return 0;
}

int tokenizer(char tokens[1000][1000],const char* read)
{
    int count = 0;
    while(*read)
    {
        if(!is_tag(*read))read++;
        else break;
    }
    const char* start = read;
    while(*read)
    {
        //example ....#hello,  , world
        //skip read until meet first,then move start = read
        if(is_tag(*read))read++;
        else
        {
            size_t len = read-start;
            memcpy(tokens[count],start,len);
            tokens[count][len] = '\0';
            count ++;
            while(*read)
            {
                if(!is_tag(*read))read++;
                else break;
            }
            start = read;
        }
    }
    //handle orphan
    if(read>start)
    {
        size_t len = read-start;
        memcpy(tokens[count],start,len);
        tokens[count][len] = '\0';
        count++;
    }
    return count;
}


int check_all_match(char inter_tokens[1000][1000],int inter_count,char tokens[1000][1000],int count)
{
    for(int i =0;i<inter_count;i++)
    {
        int found = 0;
        for(int j=0;j<count;j++)
        { 
            if(strcmp(inter_tokens[i],tokens[j])==0)found = 1;
        }
        if(!found)return 0;
    }
    return 1;
}


void send(const struct server * srv, const char * message){
    char tokens[1000][1000];
    int count = tokenizer(tokens,message);

    struct receiver* table[1000];
    int index = 0;
    struct connection* itr = srv->head;
    while(itr)
    {
        if(!itr->inter)
        {
            itr = itr->next;
            continue;
        }      
        char inter_tokens[1000][1000];
        int inter_count = tokenizer(inter_tokens,itr->inter);
        int res = check_all_match(inter_tokens,inter_count,tokens,count);
        if(res && !find_helper(table,itr->r,index))
        {
            itr->r->deliver(itr->r,message);
            table[index++] = itr->r;
        }
        itr = itr->next;
    }
}