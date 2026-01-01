#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Scoreboard

// A text file stores the results of a number of games played by a number of teams. Each line of the file represents a game and contains the names of the two teams playing the game followed by the score of the first and second team, respectively. Team names are strings of up to 20 alphanumeric ASCII characters (without spaces or other characters). Team names and scores are separated by spaces on each input line. Scores are non-negative integers. The team with the highest game score wins that game and gains 3 points in the overall tournament score. Otherwise, if the game is tied (same score for both teams) then both teams gain 1 point in the overall tournament score.

// In a source file called scoreboard.c write a C program that reads a number of game results from the standard input, and writes on the standard output the tournament scoreboard as defined below. The program takes one optional command-line argument that specifies the maximum number of teams. By default the maximum number of teams is 10.

// The scoreboard is a text file in which each line indicates a team name, the tournament score of that team, and the number of games played in the tournament by that team. The scoreboard must be sorted in decreasing order of tournament score, from highest to lowest, and if two or more teams have the same score, in alphabetical order of team names.

// As an example, below is a valid input and the corresponding expected output.

// Input:

// programmers coders 3 1
// designers programmers 2 5
// designers coders 1 1

// Output:

// programmers 6 2
// coders 1 2
// designers 1 2

// The program must exit with EXIT_FAILURE when the input is incorrect, for example if there are more than the given maximum number of teams, or if there is an error in reading the input or writing the output, or for any other failure such as in memory allocation. Recall that EXIT_FAILURE and EXIT_SUCCESS are defined in the stdlib.h standard header file. 



struct team{
    char* name;
    int score;
    int times;
};




struct team* teams = NULL;
static int count = 0;

static char* delim = " \t\n\r";


void error(char* information){
    fprintf(stderr,"%s\n",information);
    exit(EXIT_FAILURE);
}


void tokenizer(char* line,char** tokens){
    int count = 0;
    char* token = strtok(line,delim);
    while(token!=NULL){
        tokens[count++] = token;
        token = strtok(NULL,delim);
    }
    if(count != 4)error("invalid format");
}



struct team* find_helper(char* name){
    for(int i =0;i<count;i++){
        if(strcmp(teams[i].name,name)==0)return &teams[i];
    }
    return NULL;
}

int spaceline(char* line){
    while(*line){
        if(isspace(*line))line++;
        else return 0;
    }
    return 1;
}


void get_result(int amounts){
    if(amounts == 0)return ;
    teams = malloc(amounts*sizeof(struct team));
    if(!teams)error("mem");
    char line[20000];
    char** tokens = malloc(amounts*100);
    while(fgets(line,sizeof(line),stdin)){
        //check whether its empty line;
        int res = spaceline(line);
        if(res)continue;
        tokenizer(line,tokens);
        //format:
        //token[0] = team1
        //token[1] = team2
        //token[2] = team1_score
        //token[3] = team2_score
        struct team* team1 = find_helper(tokens[0]);
        int team1_score = atoi(tokens[2]);
        int team2_score = atoi(tokens[3]);
        if(team1){
            if(team1_score > team2_score)
            team1->score +=3;
            else if(team1_score == team2_score)
            team1->score ++;
            team1->times++;
        }
        else if(!team1){
            if(count >= amounts)error("overflow");
            teams[count].name = strdup(tokens[0]);
            if(!teams[count].name)error("mem");
            teams[count].times ++;
            if(team1_score > team2_score)teams[count].score +=3;
            else if(team1_score == team2_score) teams[count].score ++;
            else teams[count].score = 0;
            count ++;
        }

        struct team* team2 =find_helper(tokens[1]);
        if(team2){
            if(team2_score > team1_score)
            team2->score +=3;
            else if(team1_score == team2_score)
            team2->score ++;
            team2->times++;
        }
        else if(!team2){
            if(count >= amounts)error("overflow");
            teams[count].name = strdup(tokens[1]);
            if(!teams[count].name)error("mem");
            teams[count].times++;
            if(team2_score > team1_score)teams[count].score +=3;
            else if(team1_score == team2_score) teams[count].score ++;
            else teams[count].score = 0;
            count ++;
        }
    }
}


int compare_team(const void* a,const void* b){
    const struct team* ta = (const struct team*)a;
    const struct team* tb = (const struct team*)b;
    //based on score at first
    if(ta->score!=tb->score)return tb->score - ta->score;

    //if same,use name seq
    return strcmp(ta->name,tb->name);
}



void print(int amounts){
    if(amounts ==0)return;
    qsort(teams,count,sizeof(struct team),compare_team);
    for(int i =0;i<count;i++){
        printf("%s %d %d\n",teams[i].name,teams[i].score,teams[i].times);
    }
}











int main(int argc,char* argv[]){
    if(argc == 1){
        get_result(10);
        print(10);
    }
    else {
        get_result(atoi(argv[1]));
        print(atoi(argv[1]));
    }
}