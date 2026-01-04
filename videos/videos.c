#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "videos.h"

struct view{
    int duration;
    int full;
    struct view* next;
};

struct video{
    char* title;
    int time;
    int id;
    struct video* next;
    struct view* head_view;
};

struct platform{
    struct video* head_video;
    int size ;
};


struct platform* create()
{
    struct platform* new = malloc(sizeof(struct platform));
    if(!new)return NULL;
    new -> head_video = NULL;
    new ->size = 0;
    return new;
}

void destroy_helper_helper(struct view* v)
{
    struct view* itr = v;
    while(itr)
    {
        struct view* tmp = itr->next;
        free(itr);
        itr = tmp;
    }
}


void destroy_helper(struct video* v)
{
    struct video * itr = v;
    while(itr)
    {
        if(itr->title)free(itr->title);
        if(itr->head_view)destroy_helper_helper(itr->head_view);
        struct video* tmp = itr->next;
        free(itr);
        itr = tmp;
    }
}


void destroy(struct platform* p)
{
    if(p->head_video)destroy_helper(p->head_video);
    free(p);
}

void clear(struct platform* p)
{
    if(p->head_video)destroy_helper(p->head_video);
    p->head_video = NULL;
    p->size = 0;
}

int add_video(struct platform* p,const char* title,int minutes)
{
    int len = strlen(title);
    if(len == 0 || len > 100)return -1;

    //new video
    struct video* new = malloc(sizeof(struct video));
    if(!new)return -1;
    new->title = malloc(len+1);
    memcpy(new->title,title,len);
    new->title[len] = '\0';
    new->time = minutes;
    new->id = p->size;
    new->next = p->head_video;
    p->head_video = new;


    //size
    p->size++;
    return new->id;
}

int add_view(struct platform* p,int video_id,int minutes)
{
    struct video* itr = p->head_video;
    while(itr)
    {
        if(itr->id == video_id)
        {
            struct view* new = malloc(sizeof(struct view));
            new->duration = minutes;
            if(minutes>=itr->time)new->full =1;
            new->next = itr->head_view;
            itr->head_view = new;
            return 1;
        }
        itr = itr ->next;
    }
    return 0;
}

int total_view_minutes(struct platform* p)
{
    struct video* itr = p->head_video;
    int res = 0;
    while(itr)
    {
        if(itr->head_view)
        {
            struct view* itr_v = itr->head_view;
            while(itr_v)
            {
                res+=itr_v->duration;
                itr_v = itr_v->next;
            }
        }
        itr = itr->next;
    }
    return res;
}

int total_full_views(struct platform* p)
{
    struct video* itr = p->head_video;
    int res = 0;
    while(itr)
    {
        if(itr->head_view)
        {
            struct view* itr_v = itr->head_view;
            while(itr_v)
            {
                if(itr_v->full==1)res++;
                itr_v = itr_v->next;
            }
        }
        itr = itr->next;
    }
    return res;
}

int video_by_title(struct platform* p,const char* title)
{
    struct video* itr = p->head_video;
    while(itr)
    {
        if(itr->title&&strcmp(itr->title,title)==0){
            return itr->id;
        }
        itr = itr->next;
    }
    return -1;
}



