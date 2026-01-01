#ifndef BLOB_H_INCLUDED
#define BLOB_H_INCLUDED

#define CHUNK_MAX_LEN 100

struct chunk {
    char data[CHUNK_MAX_LEN];
    unsigned int length; 	/* number of stored chars, possibly 0 */
};

struct chunk_list {
    struct chunk * c;
    struct chunk_list * prev;
    struct chunk_list * next;
};

struct blob {
    struct chunk_list sentinel;	/* doubly-linked list with sentinel */
};

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int count_char (const struct blob * b, char c);
extern unsigned int copy_to_buffer (const struct blob * b,
				    char * buf, unsigned int maxlen);
extern unsigned int copy_to_buffer_reverse (const struct blob * b,
					    char * buf, unsigned int maxlen);

#ifdef __cplusplus
}
#endif

#endif
