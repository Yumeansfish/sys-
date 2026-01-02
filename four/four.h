#ifndef FOUR_H_INCLUDED
#define FOUR_H_INCLUDED

static const char EMPTY = ' ';
static const char PLAYER_O = 'o';
static const char PLAYER_X = 'x';

struct game;

struct game * create (int columns, int rows, char first_player);
void destroy (struct game * g);

void restart (struct game * g, char first_player);
int move (struct game * g, int column);

char get_cell (const struct game * g, int column, int row);
char get_next_player (const struct game * g);
int get_columns (const struct game * g);
int get_rows (const struct game * g);

int board_full (const struct game * g);
char outcome (const struct game * g);

#endif
