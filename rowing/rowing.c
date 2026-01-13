#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rowing.h"


struct club{
    struct person* persons;
    struct boat* boats;
    struct excursion* excursions;
};

struct person{
    char* name;
    int km;
    int time;
    int on_excursion;
    struct person* next;
};


struct boat{
    char* name;
    int capacity;
    int km;
    int time;
    int on_excursion;
    struct boat* next;
};

struct excursion{
    struct boat* boat;
    struct person** crews;
    struct club* club;
    int size;
    int capacity;
    struct excursion* next;
};


struct club* create_club()
{
    struct club* new = malloc(sizeof(struct club));
    if(!new)return NULL;
    new->persons = NULL;
    new->boats = NULL;
    new->excursions = malloc(sizeof(struct excursion));
    new->excursions->next = NULL;
    new->excursions->boat = NULL;
    new->excursions->crews = NULL;
    new->excursions->club = new;
    new->excursions->size = 0;
    new->excursions->capacity = 0;
    return new;
}

void destroy_boats(struct boat* b)
{
    while(b)
    {
        if(b->name)free(b->name);
        struct boat* tmp = b->next;
        free(b);
        b = tmp;
    }
}

void destroy_persons(struct person* p)
{
    while(p)
    {
        if(p->name)free(p->name);
        struct person* tmp = p->next;
        free(p);
        p = tmp;
    }
}

void destroy_excursions(struct excursion* e)
{
    while(e)
    {
        if(e->crews)
        {
            free(e->crews);
            e->crews = NULL;
        }
        e->club = NULL;
        struct excursion* tmp = e->next;
        free(e);
        e = tmp;
    }
}


void destroy_club(struct club* c)
{
    if(c->boats)destroy_boats(c->boats);
    if(c->persons)destroy_persons(c->persons);
    if(c->excursions)destroy_excursions(c->excursions);
    c->boats = NULL;
    c->persons = NULL;
    c->excursions = NULL;
    free(c);
}


struct boat* find_boat_helper(struct club* c,const char* name)
{
    if(!c->boats)return NULL;
    struct boat* itr = c->boats;
    while(itr)
    {
        if(strcmp(itr->name,name)==0)return itr;
        itr = itr->next;
    }
    return NULL;
}

struct person* find_person_helper(struct club* c,const char* name)
{
    if(!c->persons)return NULL;
    struct person* itr = c->persons;
    while(itr)
    {
        if(strcmp(itr->name,name)==0)return itr;
        itr = itr->next;
    }
    return NULL;
}





int add_boat(struct club* c,const char* name,unsigned int max_crew)
{
    if(max_crew<1)return 0;
    struct boat* target = find_boat_helper(c,name);
    if(target)return 0;
    struct boat* new = malloc(sizeof(struct boat));
    if(!new)return 0;
    new->capacity = max_crew;
    new->name = strdup(name);
    if(!new->name)
    {
        free(new);
        return 0;
    }
    new->km = 0;
    new->time = 0;
    new->next = c->boats;
    c->boats = new;
    new->on_excursion = 0;
    return 1;
}

int add_person(struct club* c,const char* name)
{
    struct person* target = find_person_helper(c,name);
    if(target)return 0;
    struct person* new = malloc(sizeof(struct person));
    if(!new)return 0;
    new->name = strdup(name);
    if(!new->name)
    {
        free(new);
        return 0;
    }
    new->time = 0;
    new->km = 0;
    new->next = c->persons;
    c->persons  = new;
    new->on_excursion = 0;
    return 1;
}

struct excursion* create_excursion(struct club* c)
{
    struct excursion* new = malloc(sizeof(struct excursion));
    if(!new)return 0;
    new->boat = NULL;
    new->crews = NULL;
    new->club = c;
    new->size = 0;
    new->capacity = 0;
    new->next = c->excursions->next;
    c->excursions->next = new;
    return new;
}

int use_boat(struct excursion* e,const char* name)
{
    if(!e->club)return 0 ;
    if(!e)return 0;
    struct boat* target = find_boat_helper(e->club,name);
    if(!target)return 0;
    if(target->on_excursion)return 0;
    if(e->boat)return 0;
    e->boat = target;
    target->on_excursion = 1;
    int capacity = target->capacity;
    e->capacity = capacity;
    e->crews = malloc(capacity*sizeof(struct person*));
    return 1;
}

int add_crew(struct excursion* e,const char* name)
{
    if(!e->boat)return 0;
    if(e->size>=e->capacity)return 0;
    struct person* target = find_person_helper(e->club,name);
    if(!target)return 0;
    if(target->on_excursion)return 0;
    e->crews[e->size] = target;
    target->on_excursion = 1;
    e->size++;
    return 1;
}

void remove_e_from_c(struct club* c,struct excursion* e)
{
    struct excursion* itr = c->excursions;
    while(itr->next)
    {
        if(itr->next == e)
        {
            itr->next = itr->next->next;
            return ;
        }
        else
        {
            itr = itr->next;
        }
    }
}



int close_excursion(struct excursion* e,unsigned int k)
{
    if(!e->boat)return 0;
    if(e->size ==0)return 0;
    remove_e_from_c(e->club,e);
    for(int i =0;i<e->size;i++)
    {
        e->crews[i]->time++;
        e->crews[i]->km += k;
        e->crews[i]->on_excursion = 0;
    }
    e->boat->km+=k;
    e->boat->time++;
    e->boat->on_excursion = 0;
    e->club = NULL;
    e->boat = NULL;
    if(e->crews)
    {
        free(e->crews);
        e->crews = NULL;
    }
    free(e);
    e= NULL;
    return 1;
}

void cancel_excursion(struct excursion* e)
{
    remove_e_from_c(e->club,e);
    if(e->boat)e->boat->on_excursion = 0;
    for(int i =0;i<e->size;i++)
    {
        if(e->crews[i])e->crews[i]->on_excursion = 0;
    }
    if(e->crews)
    {
        free(e->crews);
        e->crews= NULL;
    }
    e->club = NULL;
    e->boat = NULL;
    free(e);
    e= NULL;
}

int get_crew_excursions(struct club* c,const char* name)
{
    struct person* target = find_person_helper(c,name);
    if(!target)return -1;
    return target->time;
}

int get_crew_kilometers(struct club* c,const char* name)
{
    struct person* target = find_person_helper(c,name);
    if(!target)return -1;
    return target->km;
}

int boat_available(struct club* c,const char* name)
{
    struct boat* target = find_boat_helper(c,name);
    if(!target)return -1;
    if(target->on_excursion)return 0;
    return 1;
}

int get_boat_excursions(struct club* c ,const char* name)
{
    struct boat* target = find_boat_helper(c,name);
    if(!target)return -1;
    return target->time;
}

int get_boat_kilometers(struct club* c ,const char* name)
{
    struct boat* target = find_boat_helper(c,name);
    if(!target)return -1;
    return target->km;
}



