#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "media_stats.h"

struct view{
    char* user;
    double start;
    double finish;
    struct view* next;
};


struct media{
    char* title;
    double duration;
    struct media* next;
    struct view* head_view;
};

struct interval{
    double start;
    double finish;
};



static struct media* head = NULL;


struct media* find_media_helper(const char* title)
{
    struct media* itr = head;
    while(itr)
    {
        if(itr->title && strcmp(itr->title,title)==0)return itr;
        itr = itr->next;
    }
    return NULL;
}

struct view* find_view_helper(struct media* target,const char* user)
{
    struct view* itr = target->head_view;
    while(itr)
    {
        if(itr->user && strcmp(itr->user,user)==0)return itr;
        itr = itr->next;
    }
    return NULL;
}


int add_media(const char* title,double duration)
{
    if(duration<=0.0)return 0;
    struct media* target = find_media_helper(title);
    if(target)return 0;

    struct media* new = malloc(sizeof(struct media));
    if(!new)return 0;
    int len = strlen(title);
    new->title = malloc(len);
    if(!new->title)return 0;
    memcpy(new->title,title,len);
    new->title[len] = '\0';
    new->duration = duration;
    new->head_view = NULL;
    new->next = head;
    head = new;
    return 1;
}


int add_view(const char* title,const char* user,double start,double finish)
{
    struct media* target = find_media_helper(title);
    if(!target)return 0;
    double duration = target->duration;

    //check start and finish
    if(start>=finish)return 0;
    if(finish - start > duration)return 0;
    if(start<0)return 0;
    if(finish>duration)return 0;

    //always create new
    {
        struct view* new = malloc(sizeof(struct view));
        if(!new)return 0;
        int len = strlen(user);
        new->user = malloc(len+1);
        if(!new->user)return 0;
        memcpy(new->user,user,len);
        new->user[len] = '\0';
        new->start = start;
        new->finish = finish;
        new->next = target->head_view;
        target->head_view = new;
    }
    return 1;
}

void destroy_view(struct view* v)
{
    struct view* itr = v;
    while(itr)
    {
        if(itr->user)free(itr->user);
        struct view* tmp = itr->next;
        free(itr);
        itr = tmp;
    }
}


void clear_media()
{
    struct media* itr = head;
    while(itr)
    {
        if(itr->title)free(itr->title);
        if(itr->head_view)destroy_view(itr->head_view);
        itr->head_view = NULL;
        struct media* tmp = itr->next;
        free(itr);
        itr = tmp;
    }
    head = NULL;
}

void clear_views()
{
    struct media* itr = head;
    while(itr)
    {
        if(itr->head_view)destroy_view(itr->head_view);
        itr->head_view = NULL;
        itr = itr->next;
    }
}





int unique_viewers(const char * title)
{
    struct media* target = find_media_helper(title);
    if(!target)return -1;
    struct view* itr = target->head_view;
    char* table[100000];
    int res = 0;
    while(itr)
    {
        if(itr->user){
            int found = 0;
            for(int i =0;i<res;i++)
            {
                if(table[i]&&strcmp(table[i],itr->user)==0)found=1;
            }
            if(!found)table[res++] = itr->user;
        }
        itr= itr->next;
    }
    return res;
}



int compare_func(const void* a,const void* b)
{
    const struct interval* ia = (const struct interval*)a;
    const struct interval* ib = (const struct interval*)b;
    if(ia->start < ib->start)return -1;
    if(ia->start > ib->start)return 1;
    return 0;
}

double total_time_view_helper(struct media* target,const char* user)
{
    struct view* itr = target->head_view;
    struct interval table[100000];
    int size = 0;

    while(itr)
    {
        if(itr->user && strcmp(itr->user,user)==0)
        {
            struct interval tmp = {itr->start,itr->finish};
            table[size++] = tmp;
        }
        itr = itr->next;
    }
    if(size==0)return 0;
    //at that time we have a interval table 
    qsort(table,size,sizeof(struct interval),compare_func);
    //now its sorted by start time
    //because its based on start time sort,then only need check s2<=e1,if yep,then we can merge
    double res = 0;
    double current_start = table[0].start;
    double current_finish = table[0].finish;
    for(int i=1;i<size;i++)
    {
        if(table[i].start<=current_finish)
        {
            if(table[i].finish>current_finish)current_finish = table[i].finish;//update current finish interval
        
        }
        else
        {
            res += current_finish - current_start;
            current_start = table[i].start;
            current_finish = table[i].finish;
        }
        //handle orphan
    
    }
    res += current_finish - current_start;
    return res;
}

double total_time_viewed(const char * title, const char * user)
{
    struct media* target = find_media_helper(title);
    if(!target)return -1;
    double res = total_time_view_helper(target,user);
    return res;
}

//返回至少完整看过一次的用户数量 = 对每个用户都算一下total_time 如果=duration 就res++

int complete_view_helper(struct media* target,double duration)
{
    struct view* itr = target->head_view;
    int res = 0;
    char* table[100000];
    int size = 0;
    while(itr)
    {
        if(itr->user)
        {
            int found = 0;
            for(int i =0;i<size;i++)
            {
                if(strcmp(table[i],itr->user)==0){
                    found = 1;
                    break;
                }
                
            }
            if(!found)
            {
                table[size++] = itr->user;
                double time = total_time_view_helper(target,itr->user);
                if(time >=duration) res++;
        }
    
        }
        itr = itr->next;
    
}
return res;
}

int complete_views(const char * title)
{
    struct media* target = find_media_helper(title);
    if(!target)return -1;
    int res = complete_view_helper(target,target->duration);
    return res;
}

