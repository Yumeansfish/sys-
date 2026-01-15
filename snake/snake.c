#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "snake.h"

// Exercise 53. (120') In a source file called snake.c or snake.cc, write a C or C++ module that
// manages the state of a simple snake video game. The module must implement the interface defined
// by the following declarations and macros
// [download this file]
// #define SNAKE_UP 1
// #define SNAKE_DOWN 2
// #define SNAKE_LEFT 3
// #define SNAKE_RIGHT 4
// #define SNAKE_OKAY 1
// #define SNAKE_FAIL 2
// #define SNAKE_NEW 3
// struct snake;
// struct snake * snake_new (int, int, int);
// void snake_destroy (struct snake *);
// int snake_start (struct snake *, int, int, int);
// int snake_change_direction (struct snake *, int);
// int snake_step (struct snake *);
// const char * snake_get_field (const struct snake *);
// int snake_get_status (const struct snake *);
// The player controls a snake that moves across a game field consisting of a c × r rectangle of cells.
// That is, the game field consists of r rows of c cells each. The game proceeds in discrete steps. At
// each step, the head of the snake moves from its current cell to the cell immediately up or down or
// to the left or to the right. The direction of movement can be set at each step, or otherwise remains
// unchanged.
// The snake starts from a set initial position and direction of movement. Initially, the snake consists
// of a single cell, which is its head. Each movement of the head also grows the body, so that the rest
// of the body stays in the same positions. The snake grows up to a maximum length of ℓ cells, at
// which point the whole snake also starts moving following the head.
// The game field must be represented as a matrix of characters, one for each cell. An empty cell
// is represented by the space character (' '). The '@' character represents the head of the snake.
// If the length of the snake is greater than one, then the tail of the snake is represented by the '+'
// character, and if the length is greater than two, then any cell between the head and tail of the snake
// is represented by the '#' character.
// Below is an example of the initial movement of a snake of maximum length ℓ = 5 starting from
// the center of a 5 × 5 game field and moving two steps to the right, then two steps down, and then
// to the left.
// @ +@ +#@ +##
// @
// +##
// #
// @
// +#
// #
// @#
// +
// #
// @##
// +
// @### @###+
// The objective of the game is to move the snake within the rectangular game field so that the snake
// head will never collide with any other part of the snake (including the tail). If one movement step
// causes the head to fall off of the game field or to hit another part of the snake, the game is lost
// and can not progress further.
// The preprocessing macros SNAKE_UP, SNAKE_DOWN, SNAKE_LEFT, and SNAKE_RIGHT identify the
// direction of movement. The macros SNAKE_OKAY, SNAKE_FAIL, and SNAKE_NEW define the status
// of the game, as we detail below.
// 70
// Your module must define the snake structure to represents the state of one game, as well as all
// the related functions specified in detail below. Notice that each snake object is independent and
// self-contained, so two or more games must coexist, each stored in its snake object. In fact, each
// function other than the constructor (snake_new) takes and operates on a particular game object,
// which is always passed as the first parameter.
// • struct snake * snake_new (int c, int r, int l) creates a new game over a field of c ≥ 1 columns
// and r ≥ 1 rows, and with a snake that grows up to a maximum size of ℓ ≥ 1 cells. The return
// value is a valid pointer to a properly constructed object, or the null pointer in case of error
// or invalid parameters. The status of a newly created game is SNAKE_NEW and the game field
// and the snake are in an undefined state.
// • void snake_destroy (struct snake * s) destroys a game object, releasing all its allocated re-
// sources.
// • int snake_start (struct snake * s, int c, int r, int d) starts the game with the snake head ini-
// tially positioned at row r and column c, and moving in direction d. The row and column
// coordinates start from 0: (0, 0) is the upper-left corner of the game field; (c, r ) is the lower-
// right corner of a c × r game field.
// snake_start initializes the given game object so that the game can start with a first step.
// If a game was already in progress or it had ended, then snake_start resets the game. The
// given initial position (c, r ) must be contained within the game field, and the direction must
// be SNAKE_UP, SNAKE_DOWN, SNAKE_LEFT, or SNAKE_RIGHT. If the parameters are valid, the
// return value is SNAKE_OKAY and the status of the game is SNAKE_OKAY. Otherwise, the
// return value and the status of the game are SNAKE_FAIL. Notice that d defines the initial
// direction, but this function does not move the snake head from its initial position at column
// c and row r .
// • void snake_change_direction (struct snake * s, int d) changes direction for the snake head.
// This function does not itself move the head. It just sets the direction for the next step.
// • int snake_step (struct snake * s) If the game status is SNAKE_OKAY, then move the snake by
// one step. For any other game status, the function has no effect and the return value is
// SNAKE_FAIL. If the movement is valid, then the return value is SNAKE_OKAY. Otherwise, if
// the movement causes the snake head to hit itself or to fall off the game field, then the game
// is lost and the status of the game changes to SNAKE_FAIL. In this case, the return value is
// also SNAKE_FAIL.
// • const char * snake_get_field (const struct snake * s) returns a pointer to a matrix of charac-
// ters representing the game field. The matrix is stored starting from the character at the
// top-left corner of the field, continuing with the characters of the first row, left-to-right, then
// the second row, and so on until the character at the bottom-right corner of the field, which
// will be in position c × r for a snake object created with c columns and r rows.
// • int snake_get_status (const struct snake * s) returns the status of the game


static char empty = ' ';
static char head = '@';
static char tail = '+';
static char middle = '#';

struct position{
    int row;
    int col;
    char symbol;
    int flag; //0 is invalid 1 is valid
};

struct snake{
    char** board;
    int max_len;
    int row;
    int col;
    int dir;
    int len;
    int state;
    struct position* pos_table;
    int size;
    int capacity;
};


static char* board_arr = NULL;

void table_realloc(struct snake* s)
{
    int new_capacity = 0;
    if(s->capacity == 0) new_capacity = 100;
    else new_capacity = s->capacity*2;
    s->capacity = new_capacity;
    struct position* tmp = realloc(s->pos_table, s->capacity *sizeof(struct position));
    if(!tmp)return ;
    s->pos_table = tmp;
}

struct position* find_symbol_helper(struct snake* s, int row, int col)
{
    for(int i=0;i<s->size;i++)
    {
        if(s->pos_table[i].flag==1 && s->pos_table[i].row == row && s->pos_table[i].col ==col)
        return &s->pos_table[i];
    }
    return NULL;
}


struct snake* snake_new(int c,int r,int l)
{
    if(c<1||r<1||l<1)return NULL;
    struct snake* new = malloc(sizeof(struct snake));
    if(!new)return NULL;
    new->board = malloc(sizeof(char*)*r);
    if(!new->board)return NULL;
    for(int i =0;i<r;i++)
    {
        new->board[i] = malloc(sizeof(char)*c);
        if(!new->board[i])return NULL;
    }
    new->max_len = l;
    new->row = r;
    new->col = c;
    new->dir = 0;
    new->len = 1;
    new->state = SNAKE_NEW;
    new->pos_table = NULL;
    new->size = 0;
    new->capacity = 0;
    return new;
}

void snake_destroy(struct snake* s)
{
    for(int i =0;i<s->row;i++)
    {
        if(s->board[i])free(s->board[i]);
    }
    free(s->board);
    s->board = NULL;
    if(s->pos_table)
    {
        free(s->pos_table);
        s->size = 0;
        s->capacity = 0;
        s->pos_table = NULL;
    }
    free(s);
    if(board_arr)free(board_arr);
    board_arr=NULL;
}

void snake_reset(struct snake* s)
{
    for(int i =0;i<s->row;i++)
    {
        for(int j=0;j<s->col;j++)
        {
            s->board[i][j] = empty;
        }
    }
    s->len = 1;
    if(s->pos_table)
    {
        free(s->pos_table);
        s->size = 0;
        s->capacity = 0;
        s->pos_table = NULL;
    }
}

void update_board(struct snake* s)
{
    for(int i=0;i<s->row;i++)
    {
        for(int j=0;j<s->col;j++)
        {
            struct position* target = find_symbol_helper(s, i, j);
            if(!target)s->board[i][j] = empty;
            else s->board[i][j] = target->symbol;
        }
    }
}




void add_position(struct snake* s, int r, int c, char symbol)
{
    if(s->size>=s->capacity)table_realloc(s);
    s->pos_table[s->size].row = r;
    s->pos_table[s->size].col = c;
    s->pos_table[s->size].symbol = head;
    s->pos_table[s->size].flag = 1;
    s->size++;
}


int snake_start(struct snake* s,int c,int r,int d)
{
    snake_reset(s);
    if(c<0 || c>=s->col)
    {
        s->state = SNAKE_FAIL;
        return SNAKE_FAIL;
    }
    else if(r<0 || r>=s->row)
    {
        s->state = SNAKE_FAIL;
        return SNAKE_FAIL;
    }
    else if(d != SNAKE_LEFT && d!=SNAKE_RIGHT && d!=SNAKE_UP && d!=SNAKE_DOWN)
    {
        s->state = SNAKE_FAIL;
        return SNAKE_FAIL;
    }
    s->dir = d;
    s->state = SNAKE_OKAY;
    add_position(s, r, c, head);
    update_board(s);
    return SNAKE_OKAY;
}



int snake_change_direction(struct snake* s,int d)
{
    if(d != SNAKE_LEFT && d!=SNAKE_RIGHT && d!=SNAKE_UP && d!=SNAKE_DOWN)
    {
        s->state = SNAKE_FAIL;
        return SNAKE_FAIL;
    }
    s->dir = d;
    return SNAKE_OKAY;
}

struct position* find_helper(struct snake* s)
{
    for(int i=0;i<s->size;i++)
    {
        if(s->pos_table[i].flag == 1 && s->pos_table[i].symbol == head)return &s->pos_table[i];
    }
    return NULL;
}


//in the new position(size)add head
//first become tail,other middle

void update_pos_table(struct snake* s, int row, int col, int mode)
{
    if(s->size>=s->capacity)table_realloc(s);
    if(mode == 0)
    {
        // add new head first
        add_position(s, row, col, head);
        
        int found_tail = 0; 
        
        for(int i = 0; i < s->size - 1; i++)
        {
            if(s->pos_table[i].flag == 1)
            {
                if(found_tail == 0)
                {
                    //the first valid one must be tail
                    s->pos_table[i].symbol = tail; 
                    found_tail = 1;
                }
                else
                {
                    //after is middle
                    s->pos_table[i].symbol = middle;
                }
            }
        }
    }

    if(mode == 1)
    {
        if(s->max_len==1)
        {
            for(int i =0;i<s->size;i++)
            {
                if(s->pos_table[i].flag==1)
                {
                    s->pos_table[i].flag =0;
                    break;
                }
            }
            add_position(s,row,col,head);
            return ;
        }
        //make the first one to middle
        if(s->size > 0) {
            s->pos_table[s->size - 1].symbol = middle;
        }

        //add new head
        add_position(s, row, col, head);

        //make the first valid one to invalid
        for(int i = 0; i < s->size; i++)
        {
            if(s->pos_table[i].flag == 1)
            {
                s->pos_table[i].flag = 0; 
                break; 
            }
        }

        // make the first valid one to tail
        for(int i = 0; i < s->size; i++)
        {
            if(s->pos_table[i].flag == 1)
            {
                s->pos_table[i].symbol = tail; 
                break;
            }
        }
    }
}

int check_eat_self(struct snake* s)
{
    struct position* head_pos = find_helper(s);
    for(int i =0;i<s->size;i++)
    {
        if(s->pos_table[i].flag==1 && s->pos_table[i].row == head_pos->row && s->pos_table[i].col == head_pos->col && s->pos_table[i].symbol!=head){
            return 1;
        }
    }
    return 0;
}



int move_head(struct snake* s,int dir,int row,int col,int len)
{
    int new_row;
    int new_col;
    if(dir == SNAKE_RIGHT)
    {
        new_row = row;
        new_col = col+1;
    }
    else if(dir == SNAKE_DOWN)
    {
        new_row = row+1;
        new_col = col;
    }
    else if(dir == SNAKE_UP)
    {
        new_row = row-1;
        new_col = col;
    }
    else
    {
        new_row = row;
        new_col = col-1;
    }
    update_pos_table(s, new_row, new_col, 0);
    update_board(s);
    s->len ++;
    int res = check_eat_self(s);
    return res;

}


int move_snake(struct snake* s,int dir,int row,int col)
{
    int new_row;
    int new_col;
    if(dir== SNAKE_RIGHT)
    {
        new_row = row;
        new_col = col+1;
    }
    else if(dir == SNAKE_LEFT)
    {
        new_row = row;
        new_col = col-1;
    }
    else if(dir == SNAKE_UP)
    {
        new_row = row-1;
        new_col = col;
    }
    else
    {
        new_row = row+1;
        new_col = col;
    }
    update_pos_table(s, new_row, new_col, 1);
    update_board(s);
    int res = check_eat_self(s);
    return res;
}



int snake_step(struct snake* s)
{
    if(s->state != SNAKE_OKAY){
        return SNAKE_FAIL;
    }
    struct position* target= find_helper(s);
    if(!target){
        return SNAKE_FAIL;
    }
    int r = target->row;
    int c = target->col;
    int dir = s->dir;
    int res;

    int move_all = 0;
    if(s->len >= s->max_len)move_all =1;

    target = NULL;
    if(dir == SNAKE_RIGHT)
    {
        //meet the wall
        if(c+1>=s->col)
        {
            s->state = SNAKE_FAIL;
            return SNAKE_FAIL;
        }
        else if(!move_all)
        {
            int res = move_head(s,dir,r,c,s->len);
            if(res)
            {
                s->state = SNAKE_FAIL;
                return SNAKE_FAIL;
            }
            return SNAKE_OKAY;
        }
        //move all
        else
        {
            res = move_snake(s,dir,r,c);
            if(res)
            {
                s->state = SNAKE_FAIL;
                return SNAKE_FAIL;
            }
            return SNAKE_OKAY;
        }
    }
    else if(dir == SNAKE_LEFT)
    {
        if(c==0)
        {
            s->state = SNAKE_FAIL;
            return SNAKE_FAIL;
        }

        else if(!move_all)
        {
            int res = move_head(s,dir,r,c,s->len);
            if(res)
            {
                s->state = SNAKE_FAIL;
                return SNAKE_FAIL;
            }
            return SNAKE_OKAY;
        }
        //move all
        else
        {
            res = move_snake(s,dir,r,c);
            if(res)
            {
                s->state = SNAKE_FAIL;
                return SNAKE_FAIL;
            }
            return SNAKE_OKAY;
        }
    }
    else if(dir == SNAKE_UP)
    {
        if(r==0)
        {
            s->state = SNAKE_FAIL;
            return SNAKE_FAIL;
        }
        else if(!move_all)
        {
            int res = move_head(s,dir,r,c,s->len);
            if(res)
            {
                s->state = SNAKE_FAIL;
                return SNAKE_FAIL;
            }
            return SNAKE_OKAY;
        }
        //move all
        else
        {
            res = move_snake(s,dir,r,c);
            if(res)
            {
                s->state = SNAKE_FAIL;
                return SNAKE_FAIL;
            }
            return SNAKE_OKAY;
        }
    }
    else if(dir == SNAKE_DOWN)
    {
        if(r+1>=s->row)
        {
            s->state = SNAKE_FAIL;
            return SNAKE_FAIL;
        }
        else if(!move_all)
        {
            int res = move_head(s,dir,r,c,s->len);
            if(res)
            {
                s->state = SNAKE_FAIL;
                return SNAKE_FAIL;
            }
            return SNAKE_OKAY;
        }
        //move all
        else
        {
            res = move_snake(s,dir,r,c);
            if(res)
            {
                s->state = SNAKE_FAIL;
                return SNAKE_FAIL;
            }
            return SNAKE_OKAY;
        }
    }
    //dir is not valid
    else
    {
        s->state = SNAKE_FAIL;
        return SNAKE_FAIL;
    }
}


const char * snake_get_field (const struct snake * s){
    if(!s->board)return NULL;
    board_arr = malloc(sizeof(char)*s->row*s->col);
    if(!board_arr)return NULL;
    int count = 0;
    for(int i=0;i<s->row;i++)
    {
        for(int j=0;j<s->col;j++)
        {
            board_arr[count++] = s->board[i][j];
        }
    }
    return (const char*)board_arr;
}



int snake_get_status (const struct snake* s){
    return s->state;
}
