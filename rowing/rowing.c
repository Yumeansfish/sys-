#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rowing.h"



struct person {
    char* name;
    struct person* next;
    int times;
    int kms;
    int state;
};

struct ship {
    char* name;
    int capacity;
    int times;
    int kms;
    int state;//0 availale; 1 on excursion
    struct ship* next;
};

struct excursion{
    struct ship* ship;
    struct club* c;
    struct excursion* next;
    struct person **crews;
    int size;
};

struct club{
    struct ship* ships;
    struct person* members;
    struct excursion* excursions;
};

struct club* create_club(){
    struct club* res = malloc(sizeof(struct club));
    if(!res)return NULL;
    res->ships = NULL;
    res->members = NULL;
    res->excursions = NULL;
    return res;
}

void destroy_ships(struct ship* s){
    struct ship* cur = s;
    while(cur){
        if(cur->name)free(cur->name);
        struct ship* tmp = cur->next;
        free(cur);
        cur = tmp;
    }
}

void destroy_members(struct person* p){
    struct person* cur = p;
    while(cur){
        if(cur->name)free(cur->name);
        struct person* tmp = cur->next;
        free(cur);
        cur=tmp;
    }
}

void destroy_excursions(struct excursion* e){
    struct excursion* cur = e;
    while(cur){
        if(cur->crews)free(cur->crews);
        struct excursion* tmp = cur->next;
        free(cur);
        cur =tmp;
    }
}


void destroy_club(struct club* c)
{
        if(c->ships)destroy_ships(c->ships);
        if(c->members)destroy_members(c->members);
        if(c->excursions)destroy_excursions(c->excursions);
        free(c);
    }

struct ship* find_boat_club(struct ship* s,const char* name){
    while(s){
        if(strcmp(s->name,name)==0){
            return s;
        }
        s = s->next;
    }
    return NULL;
}

int add_boat(struct club* c,const char* name,unsigned int max_crew){
    if(!name)return 0;
    if(!c)return 0;
    if(max_crew<1)return 0;
    struct ship* target = find_boat_club(c->ships,name);
    if(target)return 0;
    struct ship* cur = malloc(sizeof(struct ship));
    cur->name = strdup(name);
    if(!cur->name)return 0;
    cur->capacity = max_crew;
    cur->times= 0;
    cur->kms = 0;
    cur->state = 0;
    //head insert
    cur->next = c->ships;
    c->ships = cur;
    return 1;
}
 
struct person* find_person_club(struct person* m,const char*name){
    while(m){
        if(strcmp(m->name,name)==0){
            return m;
        }
        m = m->next;
    }
    return NULL;
}

int add_person(struct club* c,const char* name){
    if(!name)return 0;
    if(!c)return 0;
    struct person* target = find_person_club(c->members,name);
    if(target)return 0;
    struct person* cur = malloc(sizeof(struct person));
    cur->name = strdup(name);
    if(!cur->name)return 0;
    cur->times= 0 ;
    cur->kms=0;
    cur->state = 0;
    //head insert
    cur->next = c->members;
    c->members = cur;
    return 1;
}

struct excursion* create_excursion(struct club* c){
    struct excursion* res = malloc(sizeof(struct excursion));
    if(!res)return NULL;
    res->c = c;
    res->ship= NULL;
    res->crews = NULL;
    res->size = 0;
    //head insert
    res->next = c->excursions;
    c->excursions = res;
    return res;
}


int use_boat(struct excursion* e,const char* name){
    if(!e)return 0;
    if(!e->c)return 0;
    if(!name)return 0;
    if(e->ship)return 0;
    struct ship* target_in_club = find_boat_club(e->c->ships,name);
    if(!target_in_club)return 0;
    if(target_in_club->state == 1)return 0;
    e->ship = target_in_club;
    target_in_club->state = 1;
    e->crews = malloc(sizeof(struct person*)*e->ship->capacity);
    return 1;
}

int add_crew(struct excursion* e,const char* name){
    if(!e)return 0;
    if(!e->ship)return 0;
    if(e->ship->capacity<e->size+1)return 0;
    struct person* target_in_club = find_person_club(e->c->members,name);
    if(!target_in_club)return 0;
    if(target_in_club->state == 1)return 0;
    target_in_club->state =1;
    e->crews[e->size] = target_in_club;
    e->size++;
    return 1;
}

void add_ships(struct ship* s,int k){
    s->kms += k;
    s->times ++;
    s->state = 0;
}

void add_crews(struct person** crews,int k,int size){
    for(int i =0;i<size;i++){
        crews[i]->kms +=k;
        if(k!=0)crews[i]->times ++;
        crews[i]->state =0;
    }
}


void remove_excursion(struct excursion *remove){
    if(!remove->c)return;
    if(!remove->c->excursions)return;
    struct excursion dummy = {NULL,NULL,remove->c->excursions,NULL,0};
    struct excursion* cur = &dummy;
    while(cur){
        if(cur->next == remove){
            cur->next = cur->next->next;
            break;
        }
        else{
            cur = cur->next;
        }
    }
    remove->c->excursions = dummy.next;
    remove->c = NULL;
}

int close_excursion(struct excursion* e,unsigned int k){
    if(!e)return 0;
    if(!e->ship)return 0;
    if(e->size==0)return 0;
    add_ships(e->ship,k);
    add_crews(e->crews,k,e->size);
    free(e->crews);
    remove_excursion(e);
    free(e);
    return 1;
}

void cancel_excursion(struct excursion* e){
    if(!e)return;
    if(e->ship)e->ship->state = 0;
    if(e->crews){add_crews(e->crews,0,e->size);
    free(e->crews);
    }
    remove_excursion(e);
    free(e);
}

int get_crew_excursions(struct club* c,const char*name){
    if(!name)return -1;
    if(!c) return -1;
    struct person* target = find_person_club(c->members,name);
    if(!target)return -1;
    return target->times;
}

int get_crew_kilometers(struct club* c,const char* name){
    if(!name)return -1;
    if(!c)return -1;
    struct person* target = find_person_club(c->members,name);
    if(!target)return -1;
    return target->kms;
}

int boat_available(struct club* c,const char* name){
    if(!c)return -1;
    if(!name)return -1;
    struct ship* target = find_boat_club(c->ships,name);
    if(!target)return -1;
    if(target->state)return 0;
    return 1;
}

int get_boat_excursions(struct club*c,const char* name){
    if(!c)return -1;
    if(!name)return -1;
    struct ship* target=find_boat_club(c->ships,name);
    if(!target)return -1;
    return target->times;
}

int get_boat_kilometers(struct club*c,const char* name){
    if(!c)return -1;
    if(!name)return -1;
    struct ship* target=find_boat_club(c->ships,name);
    if(!target)return -1;
    return target->kms;
}
