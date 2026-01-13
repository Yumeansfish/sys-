#include <assert.h>
#include "basic_testing.h"

#include "../rooms.h"

TEST(one_reservation) {
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

    assert_int_eq(make_reservation(&r, &t, "event"), 1);
    assert_int_eq(r.floor, 1);
    assert_int_eq(r.number, 2);
    assert_int_eq(t.start, 0);
    TEST_PASSED;
}

TEST(one_reservation_failed) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
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
    r.capacity = 4;
    assert_int_eq(make_reservation(&r, &t, "event"), 0);
    TEST_PASSED;
}

TEST(one_reservation_specific_floor) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = 1;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = ANY_CAPACITY;

    assert_int_eq(make_reservation(&r, &t, "event"), 1);
    assert_int_eq(r.floor, 1);
    assert_int_eq(r.number, 2);
    assert_int_eq(t.start, 0);
    TEST_PASSED;
}

TEST(one_reservation_specific_number) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = ANY_FLOOR;
    r.number = 2;
    r.capacity = ANY_CAPACITY;

    assert_int_eq(make_reservation(&r, &t, "event"), 1);
    assert_int_eq(r.floor, 1);
    assert_int_eq(r.number, 2);
    assert_int_eq(t.start, 0);
    TEST_PASSED;
}

TEST(one_reservation_specific_capacity) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 2;

    assert_int_eq(make_reservation(&r, &t, "event"), 1);
    assert_int_eq(r.floor, 1);
    assert_int_eq(r.number, 2);
    assert_int_eq(t.start, 0);
    TEST_PASSED;
}

TEST(one_reservation_specific_all) {
    room r;
    schedule t;

    clear();

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;
    room * begin = &r;
    add_rooms(begin, begin + 1);
 
    t.start = 0;
    t.finish = 1000;
    t.duration = 1;

    r.floor = 1;
    r.number = 2;
    r.capacity = 3;

    assert_int_eq(make_reservation(&r, &t, "event"), 1);
    assert_int_eq(r.floor, 1);
    assert_int_eq(r.number, 2);
    assert_int_eq(t.start, 0);
    TEST_PASSED;
}

int main() {
    RUN_TEST(one_reservation);
    RUN_TEST(one_reservation_failed);
    RUN_TEST(one_reservation_specific_floor);
    RUN_TEST(one_reservation_specific_number);
    RUN_TEST(one_reservation_specific_capacity);
    RUN_TEST(one_reservation_specific_all);
    PRINT_TEST_RESULTS;
    assert(ALL_TESTS_PASSED);
}
