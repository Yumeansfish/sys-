#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

struct path;			/* declaration of the path structure */

struct path * path_new(const char * name); /* constructor */
void path_destroy(struct path * path);	   /* destructor */

const char * path_append(struct path * this, const char * name);
const char * path_remove(struct path * this);
const char * path_value(const struct path * this);

#endif