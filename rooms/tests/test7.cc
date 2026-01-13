#include <string.h>
#include <assert.h>
#include "basic_testing.h"

#include "../rooms.h"

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

TEST(print_empty) {
    FILE* f = tmpfile();

    print_schedule(f, ANY_FLOOR, ANY_ROOM_NUMBER, 0, 1000);
    rewind(f);
    char buf[1];
    assert(fread(buf, 1, 1, f) == 0);
    fclose(f);

    TEST_PASSED;
}

TEST(print_one_empty_room) {
    init_ten_rooms();
    FILE* f = tmpfile();

    print_schedule(f, 1, 3, 0, 1000);
    rewind(f);
    char buf[256];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    buf[n] = '\0';
    assert_string_eq(buf, "room 3 floor 1:\n");
    fclose(f);

    TEST_PASSED;
}

TEST(print_one_empty_floor) {
    init_ten_rooms();
    FILE* f = tmpfile();


    print_schedule(f, 1, ANY_ROOM_NUMBER, 0, 1000);
    rewind(f);
    char buf[256];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    buf[n] = '\0';
    assert_string_eq(buf, "room 3 floor 1:\nroom 4 floor 1:\nroom 5 floor 1:\nroom 6 floor 1:\nroom 7 floor 1:\n");
    fclose(f);

    TEST_PASSED;
}

TEST(print_many_on_one_floor) {
    init_ten_rooms();

    schedule t;
    room r;
    
    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event1");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event2");

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event3");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event4");

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event5");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event6");

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event7");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event8");

    t.start = 100;
    t.finish = 200;
    t.duration = 60;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event9");

    t.start = 100;
    t.finish = 200;
    t.duration = 60;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event10");

    FILE* f = tmpfile();
    print_schedule(f, 1, ANY_ROOM_NUMBER, 0, 1000);
    rewind(f);
    char buf[512];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    buf[n] = '\0';
    assert_string_eq(buf, "\
room 3 floor 1:\n\
event 100 160 event9\n\
room 4 floor 1:\n\
room 5 floor 1:\n\
room 6 floor 1:\n\
room 7 floor 1:\n\
");
    fclose(f);

    TEST_PASSED;
}

TEST(print_many_on_one_floor2) {
    init_ten_rooms();

    schedule t;
    room r;
    
    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event1");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event2");

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event3");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event4");

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event5");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event6");

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event7");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event8");

    t.start = 100;
    t.finish = 200;
    t.duration = 60;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event9");

    t.start = 100;
    t.finish = 200;
    t.duration = 60;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event10");

    FILE* f = tmpfile();
    print_schedule(f, 3, ANY_ROOM_NUMBER, 0, 1000);
    rewind(f);
    char buf[1024];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    buf[n] = '\0';
    assert_string_eq(buf, "\
room 3 floor 3:\n\
event 0 30 event1\n\
event 30 60 event3\n\
event 60 90 event5\n\
event 100 130 event2\n\
event 130 160 event4\n\
event 160 190 event6\n\
event 190 220 event7\n\
event 220 250 event8\n\
room 4 floor 3:\n\
event 100 160 event10\n\
room 5 floor 3:\n\
room 6 floor 3:\n\
room 7 floor 3:\n\
");
    fclose(f);

    TEST_PASSED;
}

TEST(print_many_on_one_floor3) {
    init_ten_rooms();

    schedule t;
    room r;
    
    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event1");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event2");

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event3");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event4");

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event5");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event6");

    t.start = 0;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event7");

    t.start = 100;
    t.finish = 1000;
    t.duration = 30;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event8");

    t.start = 100;
    t.finish = 200;
    t.duration = 60;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event9");

    t.start = 100;
    t.finish = 200;
    t.duration = 60;
    r.floor = ANY_FLOOR;
    r.number = ANY_ROOM_NUMBER;
    r.capacity = 11;
    make_reservation(&r, &t, "event10");

    FILE* f = tmpfile();
    print_schedule(f, ANY_FLOOR, ANY_ROOM_NUMBER, 100, 200);
    rewind(f);
    char buf[1024];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    buf[n] = '\0';
    assert_string_eq(buf, "\
room 3 floor 1:\n\
event 100 160 event9\n\
room 4 floor 1:\n\
room 5 floor 1:\n\
room 6 floor 1:\n\
room 7 floor 1:\n\
room 3 floor 3:\n\
event 100 130 event2\n\
event 130 160 event4\n\
event 160 190 event6\n\
event 190 220 event7\n\
room 4 floor 3:\n\
event 100 160 event10\n\
room 5 floor 3:\n\
room 6 floor 3:\n\
room 7 floor 3:\n\
");
    fclose(f);

    TEST_PASSED;
}

int main() {
    RUN_TEST(print_empty);
    RUN_TEST(print_one_empty_room);
    RUN_TEST(print_one_empty_floor);
    RUN_TEST(print_many_on_one_floor);
    RUN_TEST(print_many_on_one_floor2);
    RUN_TEST(print_many_on_one_floor3);

    PRINT_TEST_RESULTS;
    assert(ALL_TESTS_PASSED);
}
