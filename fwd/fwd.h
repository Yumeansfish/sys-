#ifndef FWD_H_INCLUDED
#define FWD_H_INCLUDED

struct fwd_table;

/* Constructor: return the null pointer in case of failure. */
struct fwd_table * fwd_new();

/* Destructor: clear all memory allocated for the given table. */
void fwd_delete(struct fwd_table * t);

/* Associate an IPv4 prefix with an output port in the given table.
 * The prefix is a string of the format IPv4-address/prefix-length.
 * For example, the strings "127.0.0.0/8" and "128.138.196.0/19" are
 * valid prefixes.  Return 0 on failure, either because the format of
 * the given prefix is wrong, or because memory is exhausted.  Return
 * non-zero on success.
 */
int fwd_add(struct fwd_table * t, const char * prefix, int port);

/* Clear the table. */
void fwd_clear(struct fwd_table * t);

/* Return the output port for the given IPv4 address.  The output port
 * is the one associated with the longest prefix that matches the
 * given address.  Return -1 if no such prefix is found or if the
 * format of the given address is wrong.
 */
int fwd_forward(const struct fwd_table * t, const char * address);

#endif
