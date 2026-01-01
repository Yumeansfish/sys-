#include <stdlib.h>

/* Stub for reallocarray on macOS which doesn't have this function */
void *reallocarray(void *ptr, size_t nmemb, size_t size) {
    if (nmemb != 0 && size > SIZE_MAX / nmemb) {
        return NULL;
    }
    return realloc(ptr, nmemb * size);
}
