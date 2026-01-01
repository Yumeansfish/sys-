#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "stocks.h"


// Exercise Session n. 11
// Systems Programming

// We practice with a classic “database” structures, but with a twist: the structure maintains a log of time-ordered events over a given time window. This is Exercise 43 from the collection of exam exercises.
// Stocks

// In a source file called stocks.cc write a C/C++ library to manage stock trades. The library must implement the following interface:

// struct trades_log;

// struct trades_log * new_log();          /* constructor */
// void delete_log(struct trades_log * l); /* destructor */

// int new_trade(struct trades_log * l, double time,
//               const char * symbol, double price, unsigned int quantity);

// void clear(struct trades_log * l);

// void set_time_window(struct trades_log * l, double w);

// unsigned int total_quantity(const struct trades_log * l);

// double high_price(const struct trades_log * l);
// double low_price(const struct trades_log * l);

// double stock_high_price(const struct trades_log * l, const char * symbol);
// double stock_low_price(const struct trades_log * l, const char * symbol);
// double stock_avg_price(const struct trades_log * l, const char * symbol);

// A trade is a transfer of stocks from a seller to a buyer, and it is characterized by the following information:

//     the time when the trade is made, represented by a floating-point number representing seconds from a fixed initial date;
//     the symbol of the company whose stocks are traded, which is a string of at most five characters (ASCII);
//     the quantity of stocks traded, which is a positive integer;
//     the price at which the stocks are traded, which is a positive floating-point number.

// The library must implement a log of the trades made within a certain time window. The time window is 60 seconds by default, and can be set for a log

// with set_time_window(l,w). When set_time_window(l,w) reduces the window size compared to the previous value, all the trades that fall out of the new window must be removed.

// A new trade made at time
// for quantity of stock at price can be added to a log

// with new_trade(l,t,s,p,q). new_trade must check the validity of the trade, meanining that quantity and price are positive quantities, and that the time is not less than the time of any of the previous trades. new_trade must return 1 on success and 0 on failure or with invalid input.

// Notice that adding a new trade at time
// for a log with time-window must result in the effective removal of all the trades made before time . A log

// can also be explicitly cleared with clear(l).

// The library then implements a number of computations over a trade log: total_quantity(l) returns the total quantity of stocks traded within the time window of a log
// ; low_price(l) and high_price(l) return the lowest and highest price across all stocks, respectively; then stock_high_price(l,s), stock_low_price(l,s), and stock_avg_price(l,s) return the high, low, and average price for a given stock (symbol). If log is empty, then total_quantity(l), low_price(l), and high_price(l) must all return 0. Similarly, if there are no trades for stock , then stock_high_price(l,s), stock_low_price(l,s), and stock_avg_price(l,s) must all return 0. (Recall that prices and quantities are always positive values, so 0 is an invalid quantity and an invalid price.) 



struct trade{
    char name[6];
    unsigned int quantity;
    double time;
    double price;
    struct trade* next;
};

struct trades_log{
    double time_window;
    struct trade* head;
    double max_time;
};

struct trades_log *new_log(){
    struct trades_log* res = malloc(sizeof(struct trades_log));
    if(!res)return NULL;
    res -> time_window = 60;
    res -> head = NULL;
    res->max_time = 0;
    return res;
}

void destroy_trades(struct trade* t){
    if(!t)return;
    while(t){
        struct trade* tmp = t->next;
        free(t);
        t = tmp;
    }
}

void delete_log(struct trades_log *l){
    if(!l)return;
    if(l->head)destroy_trades(l->head);
    free(l);
}

struct trade* clear_outdated_trades(struct trades_log*l,double diff){
    if(!l || !l->head) return NULL;
    struct trade dummy = {{'c','\0'},0,0,0,l->head};
    struct trade* itr = &dummy;
    while(itr&&itr->next){
        //skip if < diff
        if(itr->next->time < diff){
            struct trade* tmp = itr->next;
            itr -> next = itr->next->next;
            free((tmp));
        }
        else itr = itr->next;
    }
    return dummy.next;
}


void set_time_window(struct trades_log *l,double w){
    if(!l)return;
    l->time_window = w;
    double diff = l->max_time - w;
    struct trade* res = clear_outdated_trades(l,diff);
    l->head = res;
}



int new_trade(struct trades_log*l,double time,const char* symbol,double price,unsigned int quantity){
    if(quantity <= 0 || price <= 0)return 0;
    if(time<l->max_time)return 0;
    int len = strlen(symbol);
    if(len > 5) return 0;

    struct trade* new = malloc(sizeof(struct trade));
    if(!new) return 0;
    new -> quantity = quantity;
    new -> price = price;
    new -> time = time;

    memcpy(new->name,symbol,len);
    new->name[len] = '\0';

    //head insert
    new -> next = l->head;
    l->head = new;

    if(time>l->max_time){
    l->max_time = time;
    double diff = l->max_time - l->time_window;

    //clear outdated trades
    struct trade* res = clear_outdated_trades(l,diff);
    l->head = res;
    return 1;
    }
    else return 1;
}

void clear(struct trades_log*l){
    if(!l)return;
    if(l->head)destroy_trades(l->head);
    l->max_time = 0;
    l->time_window = 60;
    l->head = NULL;
}

unsigned int total_quantity(const struct trades_log *l){
    if(!l)return 0;
    if(!l->head)return 0;
    unsigned int res = 0;
    struct trade* itr = l->head;
    while(itr){
        res += itr->quantity;
        itr = itr ->next;
    }
    return res;
}

double high_price(const struct trades_log* l){
    if(!l)return 0;
    if(!l->head)return 0;
    double max = 0;
    struct trade* itr = l->head;
    while(itr){
        if(itr->price >= max)max = itr->price;
        itr = itr->next;
    }
    return max;
}

double low_price(const struct trades_log* l){
    if(!l)return 0;
    if(!l->head)return 0;
    double min = 999999999999999999.0;
    struct trade* itr = l->head;
    while(itr){
        if(itr->price <= min) min = itr->price;
        itr = itr -> next;
    }
    return min;
}

double stock_high_price(const struct trades_log*l,const char* symbol){
    if(!l)return 0;
    if(!l->head)return 0;
    if(!symbol) return 0;
    if(strlen(symbol)>5)return 0;
    double max = 0;
    struct trade* itr = l->head;
    while(itr){
        if(strcmp(itr->name,symbol)==0){
            if(itr->price>= max){
                max = itr->price;
            }
        }
        itr = itr->next;
    }
    return max;
}

double stock_low_price(const struct trades_log *l,const char* symbol){
    if(!l || !l->head || !symbol || strlen(symbol) > 5)return 0;
    double min = 9999999999999999999.0;
    int found =0;
    struct trade* itr = l->head;
    while(itr){
        if(strcmp(itr->name,symbol)==0){
            if(itr->price <= min){
                min = itr->price;
                found = 1;
            }
        }
        itr = itr->next;
    }
    if(found == 0)return 0;
    return min;
}

double stock_avg_price(const struct trades_log *l,const char* symbol){
     if(!l || !l->head || !symbol || strlen(symbol) > 5)return 0;
     double total =0;
     int count = 0;
     struct trade* itr = l->head;
     while(itr){
        if(strcmp(itr->name,symbol)==0){
            total += itr->price;
            count ++;
        }
        itr = itr->next;
    }
    if(count == 0)return 0;
    else return total/count;

}