#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#define MAX_TYPENAME_LEN 256

#define TS_SUCCESS		0
#define TS_TRUE			1
#define TS_FALSE		0
#define TS_OUT_OF_MEMORY	-1
#define TS_TYPE_EXISTS		-2
#define TS_UNKNOWN_TYPE		-3
#define TS_UNKNOWN_SUPERTYPE	-4
#define TS_BAD_TYPENAME		-5
#define TS_NO_ELEMENTS		-6

struct type_system * create();
void destroy(struct type_system * ts);

int add_type (struct type_system * ts, const char * type_name, const char * supertype);
int types_count (struct type_system * ts);
int is_subtype (struct type_system * ts, const char * subtype, const char * supertype);

int add_element (struct type_system * ts, const char * type_name);
int remove_element (struct type_system * ts, const char * type_name);
int elements_count (struct type_system * ts, const char * type_name);
int elements_subtype_count (struct type_system * ts, const char * type_name);

#endif
