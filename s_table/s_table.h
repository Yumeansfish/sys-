#ifndef S_TABLE_H_INCLUDED
#define S_TABLE_H_INCLUDED
#include <stddef.h>
#include <stdio.h>

struct s_table;

/* Create and return a new s_table object.  Return 0 on failure. */
struct s_table * s_table_new();

/* Destroy the given s_table object and release all memory allocated by it. */
void s_table_delete(struct s_table * t);

void s_table_clear(struct s_table * t);

/* Add a record given by the given string
 * Return 0 on failure, 1 on success. */
int s_table_add_record(struct s_table * t, const char * begin, const char * end);

/* Remove a record with the given string
 * Return 0 if not found, 1 if found (and removed). */
int s_table_remove_record(struct s_table * t, const char * begin, const char * end);

/* Record processor: takes a record and returns an int
 */
typedef int (*feature_extractor)(const char * begin, const char * end);

/* Remove all the records that are selected by the given callback
 * function. A record is selected if the selector callback returns an
 * integer value that compares TRUE (i.e., != 0).
 *
 * Return the number of records that were removed. */
size_t s_table_remove_records(struct s_table * t, feature_extractor selector_callback);

/* Find a record with the maximal feature extracted by the given
 * callback function.  Copies the corresponding record in the given
 * buffer, defined by the record char pointer and the given max buffer
 * length.  Never copies more than record_max_len characters.
 *
 * Return the number of characters copied in the record buffer, or 0 
 * if there are no records in the table. */
size_t s_table_max_feature(struct s_table * t, feature_extractor feature_callback,
			   char * record, size_t record_max_len);

/* Print the table on the given FILE stream, one record per line, with
 * the records sorted in increasing order of the feature extracted by
 * the given callback function. */
void s_table_print_sorted(struct s_table * t, FILE * f,
			  feature_extractor feature_callback);
#endif