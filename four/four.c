#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"four.h"

// Exercise Session n. 10
// Systems Programming

// Let’s write a computer game! We’ll start with a simple, turn-based game called Connect Four.
// Connect Four

// In a source file called four.c implement the functions and structures declared as follows (declarations taken from four.h):

// static const char EMPTY = ' ';
// static const char PLAYER_O = 'o';
// static const char PLAYER_X = 'x';

// struct game;

// struct game * create (int columns, int rows, char first_player);
// void destroy (struct game * g);

// void restart (struct game * g, char first_player);
// int move (struct game * g, int column);

// char get_cell (const struct game * g, int column, int row);
// char get_next_player (const struct game * g);
// int get_columns (const struct game * g);
// int get_rows (const struct game * g);

// int board_full (const struct game * g);
// char outcome (const struct game * g);

// A struct game implements the state of a Connect Four game. The game consists of a rectangular board whose cells are all empty at the beginning of the game. There are two players, identified by their two marker characters defined by the constants PLAYER_O and PLAYER_X, who play the game by alternating moves. Each move consists in marking the lowest empty cell on a chosen column. A player who manages to mark four lines in a row, either horizontally, vertically, or diagonally, wins the game. An object of type struct game implements the state and evolution of a game.

// create(c,r,p) creates a new game with a board of c columns and r rows where player p moves first. c and r must be positive integers. p must be either PLAYER_O or PLAYER_X. When we say that a parameter “must be”, say, a positive integer here, we mean that the parameter can be assumed to be a positive integer.

// destroy(g) destroys a previously created game object, properly releasing all the resources allocated by it.

// restart(g,p) restarts a game, making p start with the first move.

// move(g,c) executes a move by selecting column c for the next player. Column numbers start from 0. The return value is 1 on success, or 0 on failure, which occurs if the selected column does not exist or is already full.

// get_cell(g,c,r) returns the content of the cell in column c and row r. If the cell coordinates are invalid, the behavior is undefined.

// get_next_player(g) returns the identifier of the player that is scheduled to move next in game g.

// get_columns(g) and get_rows(g) return the number of columns and rows in the board of game g, respectively.

// board_full(g) indicates whether the board is full.

// outcome(g) indicates the outcome of the game in the current state of the board. The result must be PLAYER_O or PLAYER_X if PLAYER_O or PLAYER_X is the sole winner, respectively. A player is the sole winner if the board contains four of the player’s markers in a row and does not contain a row of four markers of the other player. If none of the player has four markers in a row, then the return value must be 0. If both players have four markers in a row, then the return must be either PLAYER_O or PLAYER_X.
// Main Game Program

// In a source file called four_game.c write a C program that uses the functions declared in the header file four.h to implement a text-based version of the Connect Four game. By default, without command-line arguments, the game starts with a board of 7 columns and 7 rows, and with the O making the first move. These settings can be changes with three optional command-line arguments:

// ./four_game [<columns>] [<rows>] [<starting-player>]

// For example, the command line

// ./four_game 17 10 x

// starts a new game with a board of 17 columns and 10 rows with the X player as the starting player.

// The program displays the board, prompts the next player to move, and then reads a command from the standard input. If the command is a number, that is interpreted as the column that defines the next move. If the move is valid, the program indicates the move by printing the player marker (o or x) and on the next line an arrow realized with the v character, both aligned vertically with the position of the chosen column (see example below). The program then loops back to showing the updated board and reading the next command.

// The board is printed with an initial line of dash characters (-), with one dash for each column position, delimiting the top edge of the board. Then each row is printed, from top to bottom. Each character in each row represents a cell, and can be EMPTY (' '), PLAYER_O ('o'), or PLAYER_X ('x'). The bottom edge of the board is also printed as a list of dash characters. Following the edge is a line that indicates the column positions, each with a character between '1' and '0'. For example, the line corresponding to a board of 17 column would be 01234567890123456.

// For example, below is the first output of ./four_game 17 10 x before the program reads the first command. Notice that each line of the board consists of 17 spaces. The prompt is always either the line “Player 'x' to move:” or the line “Player 'o' to move:”.

// -----------------
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
// -----------------
// 01234567890123456
// Player 'x' to move:

// Suppose that in this example, the program read the number 3 as the input command, then the program outputs the move, the updated board, and the next prompt, as follows:

//    x
//    v
// -----------------
                 
                 
                 
                 
                 
                 
                 
                 
                 
//    x             
// -----------------
// 01234567890123456
// Player 'o' to move:

// The following is another example obtained with the command ./four_game 7 7 x with input moves 2 3 2 2 4 3 5 4 2 5 1 6 3 2. The example shows the last move, the board, and the prompt.

//   o
//   v
// -------
       
       
//   o    
//   x    
//   ox   
//   xooo 
//  xxoxxo
// -------
// 0123456
// Player 'x' to move:

// If the input command is a number that is outside the range of valid column numbers, the program outputs the line “Illegal move.” and then goes back to reading a command.

// There are two other valid commands. One is the command to restart the game, which is r x or r o to restart the game with the first for player O or player X, respectively. The other command is q, which immediately terminates the game. The game also terminates immediately at the end of the input stream.

// In any other case, the program reads each non-white-space character as an invalid command, and therefore prints the line “Invalid command.” and then cycles back to reading the next command.

// If a move results in a line of four contiguous pieces, the player that made that move wins, and the program terminates printing the line “Player 'o' wins!” or the line “Player 'x' wins!”. If no player wins and a move fills the board completely, then the game terminates with the output line “Game over.” 



struct game{
    int col;
    int row;
    char next;
    char** board;
    char outcome;
};


void reset(struct game* g){
    for(int i =0;i<g->row;i++){
        for(int j =0;j<g->col;j++){
            g->board[i][j] = EMPTY;
        }
    } 
}

void error(char* info){
    fprintf(stderr,"%s\n",info);
    exit(1);
}



struct game* create(int cols,int rows,char first_player){
    if(cols<=0||rows<=0)return NULL;
    if(first_player!= PLAYER_O && first_player != PLAYER_X)return NULL;
    struct game* res = malloc(sizeof(struct game));
    if(!res)return NULL;
    res -> col = cols;
    res -> row = rows;
    res -> next = first_player;
    res -> outcome = 0;

    //create board
    res -> board = malloc(rows*sizeof(char*));
    if(!res->board)return NULL;
    for(int i =0;i<rows;i++){
        res->board[i] = malloc(cols*sizeof(char));
        if(!res->board[i])return NULL;
    }
    reset(res);
    return res;
}

void destroy_board(struct game* g){
    for(int i=0;i<g->row;i++){
        free(g->board[i]);
}
free(g->board);
}



void destroy(struct game* game){
    if(!game)return;
    if(game->board)destroy_board(game);
    free(game);
}

void restart(struct game* g,char p){
    if(!g)return;
    if(p!=PLAYER_O&&p!=PLAYER_X)return;
    if(g->board)reset(g);
    g->next=p;
    g->outcome = EMPTY;
}


int find_row_helper(struct game*g,int col){
    int max = -1;
    for(int i =0;i<g->row;i++){
        if(g->board[i][col] == EMPTY){
            if(i>=max)max = i;
        }
    }
    return max;
}

int check_row(struct game* g,int i,int j){
    //check row
    char ** b = g->board;
    //go up
    int count = 1;
    int l = i-1;
    while(l>=0 && b[l][j] == b[i][j]){
        count ++;
        l--;
    }
    l = i+1;
    while(l<g->row && b[l][j]==b[i][j]){
        count ++;
        l++;
    }
    if(count>=4)return 1;
    return 0;
}

int check_col(struct game*g,int i,int j){
    //check col
    char ** b = g->board;
    //go left
    int count = 1;
    int l = j-1;
    while(l>=0 &&b[i][l] == b[i][j]){
        count ++;
        l --;
    }
    l =j+1;
    while(l<g->col &&b[i][l]==b[i][j]){
        count++;
        l++;
    }
    if(count>=4)return 1;
    return 0;
}

int check_dig(struct game*g,int i,int j){
    //go left up
    char ** b = g->board;
    int count = 1;
    int l = i-1;
    int k = j-1;
    while(l>=0 && k >=0&&b[l][k]==b[i][j]){
        count ++;
        l--;
        k--;
    }
    l=i+1;
    k=j+1;
    while(l<g->row&&k<g->col&&b[l][k]==b[i][j]){
        count++;
        l++;
        k++;
    }
    if(count >=4)return 1;
    return 0;
}


int check_win(struct game*g,int i,int j){
    return check_row(g,i,j) || check_col(g,i,j) || check_dig(g,i,j);
}




void update_outcome(struct game* g,int i,int j){
    if(check_win(g,i,j)){
        g->outcome = g->board[i][j];
    }
}


int move (struct game * g, int col){
    if(!g)return 0;
    if(col<0 || col>=g->col)return 0;
    int row = find_row_helper(g,col);
    if(row == -1)return 0;
    g->board[row][col] = g->next;
    if(g->next == PLAYER_O)g->next = PLAYER_X;
    else if (g->next == PLAYER_X)g->next = PLAYER_O;
    update_outcome(g,row,col);
    return 1;
}

char get_cell(const struct game*g,int col,int row){
    if(col<0 || col>=g->col || row<0 ||row >=g->row)error("UB");
    return g->board[row][col];
}

char get_next_player(const struct game* g){
    return g->next;
}

int get_columns(const struct game* g){
    return g->col;
}

int get_rows(const struct game* g){
    return g->row;
}

int board_full(const struct game* g){
    for(int i =0;i<g->row;i++){
        for(int j=0;j<g->col;j++){
            if(g->board[i][j]==EMPTY)return 0;
        }
    }
    return 1;
}

char outcome(const struct game* g){
    return g->outcome;
}



int main(int argc,char* argv[]){
    if(argc == 1){
        create(7,7,PLAYER_O);
    }
    else{
        create(atoi(argv[2]),atoi(argv[1]),argv[3][0]);
    }
}