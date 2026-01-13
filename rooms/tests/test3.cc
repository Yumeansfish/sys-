#include <assert.h>
#include "basic_testing.h"

#include "../rooms.h"

TEST(multi_reservation) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    assert_int_eq(make_reservation(&r, &t, "event1"), 1);
    assert_int_eq(r.floor, 1);
    assert_int_eq(r.number, 2);
    assert_int_eq(t.start, 0);

    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    t.start = 2000;
    t.finish = 3000;
    t.duration = 1;
    assert_int_eq(make_reservation(&r, &t, "event2"), 1);
    assert_int_eq(r.floor, 1);
    assert_int_eq(r.number, 2);
    assert_int_eq(t.start, 2000);

    TEST_PASSED;
}

void init_ten_rooms() {
    room R[] = {
	{.floor = 1, .number = 3, .capacity = 12},
	{.floor = 1, .number = 4, .capacity = 9},
	{.floor = 1, .number = 5, .capacity = 8},
	{.floor = 1, .number = 6, .capacity = 7},
	{.floor = 1, .number = 7, .capacity = 6},
	{.floor = 3, .number = 3, .capacity = 11},
	{.floor = 3, .number = 4, .capacity = 12},
	{.floor = 3, .number = 5, .capacity = 13},
	{.floor = 3, .number = 6, .capacity = 9},
	{.floor = 3, .number = 7, .capacity = 10}
    };

    clear();

    add_rooms(R, R + 10);
}

TEST(multi_room_failed) {
    room r;
    schedule t;
 
    init_ten_rooms();

    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = 2;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;
    assert_int_eq(make_reservation(&r, &t, "event"), 0);

    r.floor = ANY_FLOOR;
    r.number = 1;
    r.capacity = ANY_CAPACITY;
    assert_int_eq(make_reservation(&r, &t, "event"), 0);

    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 16;
    assert_int_eq(make_reservation(&r, &t, "event"), 0);
    TEST_PASSED;
}

TEST(multi_reservation_specific_floor) {
    room r;
    schedule t;

    init_ten_rooms();
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = 1;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;

    assert_int_eq(make_reservation(&r, &t, "event"), 1);
    assert_int_eq(r.floor, 1);
    assert_int_eq(r.number, 7);
    assert_int_eq(r.capacity, 6);
    assert_int_eq(t.start, 0);
    TEST_PASSED;
}

TEST(multi_reservation_specific_number) {
    room r;
    schedule t;

    init_ten_rooms();
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = ANY_FLOOR;
    r.number = 3;
    r.capacity = ANY_CAPACITY;

    assert_int_eq(make_reservation(&r, &t, "event"), 1);
    assert_int_eq(r.floor, 3);
    assert_int_eq(r.number, 3);
    assert_int_eq(r.capacity, 11);
    assert_int_eq(t.start, 0);
    TEST_PASSED;
}

TEST(multi_reservation_specific_capacity) {
    room r;
    schedule t;

    init_ten_rooms();
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;

    assert_int_eq(make_reservation(&r, &t, "event"), 1);
    assert_int_eq(r.floor, 3);
    assert_int_eq(r.number, 3);
    assert_int_eq(r.capacity, 11);
    assert_int_eq(t.start, 0);
    TEST_PASSED;
}

TEST(multi_reservation_specific_capacity2) {
    room r;
    schedule t;

    init_ten_rooms();
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 12;

    assert_int_eq(make_reservation(&r, &t, "event"), 1);
    assert_int_eq(r.floor, 1);
    assert_int_eq(r.number, 3);
    assert_int_eq(r.capacity, 12);
    assert_int_eq(t.start, 0);
    TEST_PASSED;
}

int main() {
    RUN_TEST(multi_reservation);
    RUN_TEST(multi_room_failed);
    RUN_TEST(multi_reservation_specific_floor);
    RUN_TEST(multi_reservation_specific_number);
    RUN_TEST(multi_reservation_specific_capacity);
    RUN_TEST(multi_reservation_specific_capacity2);

    PRINT_TEST_RESULTS;
    assert(ALL_TESTS_PASSED);
}
