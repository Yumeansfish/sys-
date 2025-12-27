struct ochecker;

struct ochecker * oc_create ();
void oc_destroy (struct ochecker * oc);

int oc_open_file (struct ochecker * oc, const char * fname);
int oc_open_mem (struct ochecker * oc, const char * begin, const char * end);
int oc_open_str (struct ochecker * oc, const char * s);

int oc_putc (struct ochecker * oc, char c);
int oc_puts (struct ochecker * oc, const char * s);
int oc_write (struct ochecker * oc, const char * buf, size_t len);
int oc_close (struct ochecker * oc);

typedef enum { OC_CLOSED = 1, OC_OPEN = 2, OC_ERROR = 3 } oc_status_t;

oc_status_t oc_status (const struct ochecker * oc);

size_t oc_position (const struct ochecker * oc);
size_t oc_line (const struct ochecker * oc);
size_t oc_column (const struct ochecker * oc);
