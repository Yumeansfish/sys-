#include<stdio.h>
#include<string.h>
#include<stdlib.h>


static char* par = "()[]{}";

static char stack[1001];
static int top = 0;//point to next position will write in stack

void error(char* info){
    fprintf(stderr,"%s\n",info);
    exit(1);
}

// OpenClose

// In a source file called openclose.c write a program that copies its standard input to its standard output by filtering certain parts of each input line as follows.

// The program is given a set of pairs of characters
// , where is the “closer” character corresponding to the “opener” character . The pairs of opener and closer characters are given as a single string “” of length

// passed to the program as its first command-line argument. For example, if the first argument is the string bdpq, then that means that opener characters b and p are associated with closer characters d and q, respectively. By default, the program uses the string “()[]{}” to define the opener/closer character pairs.

// The program copies lines from the standard input to the standard output, except that a pair of characters
// , where an opener character is followed by the corresponding closer character , is omitted (not copied to the output) if and are consecutive characters in the input line (one right after the other), or if every other character between and

// is also omitted according to this rule. For example, with the default opener/closer characters, an input line --{-}-{[]}- is copied to the output as --{-}--. With bdpq as openers/closers, an input line Ciao babdba qppqpqqbpd is copied to the output as Ciao baba qbpd.

// Input lines are properly terminated by the end-of-line character ('\n') and do not contain more than 1000 characters. 



int check_match(char c1,char c2){
    char* read = par;
    while(*read){
        if(c1==*read && c2==*(read+1))return 1;
        read+=2;
    }
    return 0;
}

void stack_add(char ch){
    //if top ==0,directly add and return
    if(top==0)
    {
        stack[top++] = ch;
        return;
    }

    //if match,top--;
    if(top-1 <0)return;
    char top_ch = stack[top-1];
    if(check_match(top_ch,ch))
    {
        top--;
        return;
    }
    else{
        stack[top++] = ch;
        return;
    }
}



// //why this is bus error?what happened?
// //char line[1001];
// //while(*line){
// stack_add(*line);
// }


void print(){
    char line[1001];
    char* read = line;
    while(fgets(line,sizeof(line),stdin)){
        read = line;
        while(*read){
            stack_add(*read);
            read++;
        }      
        stack[top] = '\0';
        printf("%s",stack);
        top = 0;
    }
}





int main(int argc,char* argv[]){
    if(argc == 1){
        print();
        return 0;
    }
    else if(argc ==2){
        if(strlen(argv[1])%2!=0)error("invalid format");
        par = argv[1];
        print();
        return 0;
    }
    else error("invalid format");
}