#ifndef ROOMS_H_INCLUDED
#define ROOMS_H_INCLUDED

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

struct room {
    int floor;
    int number;
    int capacity;
};

const int ANY_FLOOR = -1;
const int ANY_ROOM_NUMBER = -1;
const int ANY_CAPACITY = -1;

struct schedule {
    int start;
    int finish;
    int duration;
};

void clear();
void add_rooms(const struct room * begin, const struct room * end);
int make_reservation(struct room * r, struct schedule * t, const char * event);
int cancel_reservation(int floor, int number, int start);
void print_schedule(FILE * output,
		    int floor, int number, int start, int finish);

#ifdef __cplusplus
}
#endif

#endif
