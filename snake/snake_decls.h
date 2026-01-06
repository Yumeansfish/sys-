#define SNAKE_UP 1
#define SNAKE_DOWN 2
#define SNAKE_LEFT 3
#define SNAKE_RIGHT 4
#define SNAKE_OKAY 1
#define SNAKE_FAIL 2
#define SNAKE_NEW 3

struct snake;

struct snake * snake_new (int, int, int);
void snake_destroy (struct snake *);
int snake_start (struct snake *, int, int, int);
int snake_change_direction (struct snake *, int);
int snake_step (struct snake *);
const char * snake_get_field (const struct snake *);
int snake_get_status (const struct snake *);
