#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "rooms.h"

struct reservation{
    int start;
    int finish;
    char* event;
    struct reservation* next;
};


struct room_info{
    int capacity;
    int floor;
    int number;
    struct reservation* head; 
};

static struct room_info* table = NULL;
static int size = 0;
static int capacity = 0;

void room_info_realloc()
{
    int new_capacity = 0;
    if(capacity ==0)new_capacity = 100;
    else new_capacity = capacity*2;
    capacity = new_capacity;
    struct room_info* tmp = realloc(table,capacity*sizeof(struct room_info));
    if(!tmp)return;
    table = tmp;  
}

struct room_info* find_helper(int floor,int number)
{
    for(int i =0;i<size;i++)
    {
        if(table[i].floor == floor && table[i].number == number)return &table[i];
    }
    return NULL;
}

void destroy_reservation(struct reservation* itr)
{
    while(itr)
    {
        struct reservation* tmp = itr->next;
        if(itr->event)free(itr->event);
        free(itr);
        itr = tmp;
    }
}

void clear()
{
    if(table)
    {
        for(int i =0;i<size;i++)
        {
            if(table[i].head)destroy_reservation(table[i].head);
        }
    }
    free(table);
}

void add_rooms(const struct room* begin,const struct room* end)
{
    while(end > begin)
    {
        struct room_info* target = find_helper(begin->floor,begin->number);
        if(target) target->capacity = begin->capacity;
        else
        {
        if(size>=capacity)room_info_realloc();
        table[size].floor = begin->floor;
        table[size].number = begin->number;
        table[size].capacity = begin->capacity;
        table[size].head = NULL;
        size++;
        }
        begin++;
    }
}



int check_time(struct room_info cur,int start,int finish)
{
    struct reservation* itr = cur.head;
    while(itr)
    {
        if(start<itr->finish &&finish>itr->start)
        {
            return 0;
        }
        itr = itr->next;
    }
    return 1;
}

int compare_func(const void*a,const void*b)
{
    const struct room_info* ra= (const struct room_info*)a;
    const struct room_info* rb= (const struct room_info*)b;
    if(ra->capacity!=rb->capacity)return ra->capacity - rb->capacity;
    if(ra->floor!=rb->floor)return ra->floor-rb->floor;
    if(ra->number!=rb->number)return ra->number - rb->number;
    //should happen
    return -1;
}



int make_reservation(struct room * r, struct schedule * t, const char * event)
{
    struct room_info filter[10000];
    int count = 0;
    for(int i =0;i<size;i++)
    {
        int match = 1;
        if(r->capacity!=ANY_CAPACITY && r->capacity > table[i].capacity)match = 0;
        if(r->number!=ANY_ROOM_NUMBER && r->number != table[i].number)match = 0;
        if(r->floor!=ANY_FLOOR && r->floor > table[i].floor)match = 0;
        if(match)filter[count++] = table[i];
    }
    qsort(filter,count,sizeof(struct room_info),compare_func);
    //check t
    int start = t->start;
    int finish = t->finish;
    int duration = t->duration;
    for(int i=0;i<count;i++)
    {
        for(int s=start;s+duration<finish;s++)
        {
            int real_finish = s + duration;
            int res = check_time(filter[i],s,real_finish);
            if(res)
            {
                t->start = s;
                t->finish = real_finish;
                r->capacity = filter[i].capacity;
                r->floor = filter[i].floor;
                r->number = filter[i].number;
                struct room_info* real_room = find_helper(r->floor,r->number);
                struct reservation* new = malloc(sizeof(struct reservation));
                if(!new)return 0;
                new->start =s;
                new->finish = real_finish;
                new->event = strdup(event);
                if(!new->event)return 0;
                new->next = real_room->head;
                real_room->head = new;
                return 1;
            }
        }
    }
    return -1;  
}

int cancel_reservation(int floor, int number, int start)
{
    struct room_info* target = find_helper(floor,number);
    if(!target)return 0;
    struct reservation dummy = {0,0,NULL,target->head};
    struct reservation* itr = &dummy;
    while(itr->next)
    {
        if(itr->next->start == start)
        {   
            struct reservation* tmp = itr->next;
            itr->next = itr->next->next;
            if(tmp->event)free(tmp->event);
            free(tmp);
            return 1;
        }
        else
        {
            itr = itr->next;
        }
    }
    return 0;
}

int compare_func_v2(const void*a,const void*b)
{
    const struct room_info* ra= (const struct room_info*)a;
    const struct room_info* rb= (const struct room_info*)b;
    if(ra->floor!=rb->floor)return ra->floor-rb->floor;
    if(ra->number!=rb->number)return ra->number - rb->number;
    //should not happen
    return -1;
}

int compare_func_v3(const void*a,const void*b)
{
    const struct reservation* ra = (const struct reservation*)a;
    const struct reservation* rb = (const struct reservation*)b;
    return ra->start - rb->start;
}


void print_schedule(FILE * output,
		    int floor, int number, int start, int finish)
{
    struct room_info filter[1000];
    int count = 0;
    for(int i =0;i<size;i++)
    {
        int match = 1;
        if(number!=ANY_ROOM_NUMBER && number != table[i].number)match = 0;
        if(floor!=ANY_FLOOR && floor > table[i].floor)match = 0;
        if(match)filter[count++] = table[i];
    }
    qsort(filter,count,sizeof(struct room_info),compare_func_v2);
    for(int i =0;i<count;i++)
    {
        fprintf(output,"room %d floor %d\n",filter[i].number,filter[i].floor);
        struct reservation* itr = filter[i].head;
        struct reservation arr[1000];
        int size = 0;
        while(itr)
        {
            if(itr->start<=finish && itr->finish>=start)
            {
                arr[size++] = *itr;
            }
            itr = itr->next;
        }
        if(size)
        {
            qsort(arr,size,sizeof(struct reservation),compare_func_v3);
            for(int i=0;i<size;i++)
            {
                fprintf(output,"event: %d %d %s\n",arr[i].start,arr[i].finish,arr[i].event);
            }
        }
    }
}
        

