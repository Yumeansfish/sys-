#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"videos.h"
#define pl platform

struct view{
    int duration;
    int full;
};


struct video{
    char* title;
    int id;
    int time;
    struct view* views;
    int size;
    int capacity;
};


struct pl{
    struct video* videos;
    int size;
    int capacity;
};

void videos_realloc(struct pl* p)
{
    int new_capacity = 0 ;
    if(p->capacity ==0)new_capacity = 10;
    else new_capacity = (p->capacity) *2;
    struct video* tmp = realloc(p->videos,new_capacity*sizeof(struct video));
    if(!tmp)return;
    p->videos = tmp;
    p->capacity = new_capacity;
}

void views_realloc(struct video* v)
{
    int new_capacity = 0;
    if(v->capacity ==0)new_capacity = 10;
    else new_capacity = (v->capacity*2);
    struct view* tmp = realloc(v->views,new_capacity*sizeof(struct view));
    if(!tmp)return ;
    v->views = tmp;
    v->capacity = new_capacity;
}

struct pl* create()
{
    struct pl* new = malloc(sizeof(struct pl));
    if(!new)return NULL;
    new->videos = NULL;
    new->size = 0;
    new->capacity = 0;
    return new;
}




void destroy(struct pl* p)
{
    if(p->videos)
    {
        for(int i=0;i<p->size;i++)
        {
            if(p->videos[i].title)free(p->videos[i].title);
            if(p->videos[i].views)free(p->videos[i].views);
        }
        free(p->videos);
    }
    free(p);
}

void clear(struct pl* p)
{
    if(p->videos)
    {
        for(int i=0;i<p->size;i++)
        {
            if(p->videos[i].title)free(p->videos[i].title);
            if(p->videos[i].views)free(p->videos[i].views);
        }
        free(p->videos);
    }
    p->size = 0;
    p->capacity = 0;
    p->videos = NULL;
}




int add_video(struct pl*p,const char* title,int minutes)
{
    int len = strlen(title);
    if(len==0||len>100)return -1;
    if(minutes<0)return -1;
    if(p->size >= p->capacity)videos_realloc(p);
    p->videos[p->size].time = minutes;
    p->videos[p->size].title = malloc(len+1);
    memcpy(p->videos[p->size].title,title,len);
    p->videos[p->size].title[len] = '\0';
    p->videos[p->size].id = p->size;
    p->videos[p->size].views = NULL;
    p->videos[p->size].size = 0;
    p->videos[p->size].capacity = 0;
    p->size++;
    return p->videos[p->size-1].id;
}

int add_view(struct pl*p,int video_id,int minutes)
{
    if(minutes<0)return 0;
    if(video_id>=p->size)return 0;

    struct video* target = &p->videos[video_id];

    if(target->size>=target->capacity)views_realloc(target);

    target->views[target->size].duration = minutes;
    if(minutes>=target->time)
    target->views[target->size].full = 1;
    else target->views[target->size].full = 0;

    target->size ++;
    return 1;
}

int total_view_minutes(struct pl* p)
{
    int res =0;
    for(int i=0;i<p->size;i++)
    {
        for(int j=0;j<p->videos[i].size;j++)
        {
            res += p->videos[i].views[j].duration;
        }
    }
    return res;
}

int total_full_views(struct pl*p)
{
    int res=0;
    for(int i=0;i<p->size;i++)
    {
        for(int j=0;j<p->videos[i].size;j++)
        {
            res+=p->videos[i].views[j].full;
        }
    }
    return res;
}

int video_by_title(struct pl*p,const char* title)
{
    for(int i=0;i<p->size;i++)
    {
        if(strcmp(p->videos[i].title,title)==0)return p->videos[i].id;
    }
    return -1;
}

