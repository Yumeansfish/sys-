#ifdef __APPLE__
/* macOS compatibility layer for memory wrapping */
#include <stdlib.h>
#include <stdint.h>

void *__real_malloc(size_t size) {
    return malloc(size);
}

void __real_free(void *ptr) {
    free(ptr);
}

void *__real_realloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}

void *__real_calloc(size_t nmemb, size_t size) {
    return calloc(nmemb, size);
}

/* macOS doesn't have reallocarray, implement it */
void *__real_reallocarray(void *ptr, size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0 || SIZE_MAX / nmemb <= size)
        return NULL;
    return realloc(ptr, nmemb * size);
}
#endif
