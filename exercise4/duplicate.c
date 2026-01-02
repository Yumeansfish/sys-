#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//mode 0 = -d
//mode 1 = -u
//mode 2 = -d -n
//mode 3 = -u -n



// Duplicate lines

// Write a program called duplicate_lines that prints duplicate lines or non-duplicate lines in its standard input or in a given file. A duplicate line is a line that appears two or more times consecutively. Without command-line arguments, the program reads its input from the standard input and prints only the first of a sequence of duplicate lines. The program’s behavior can also be controlled with the following command-line arguments:

// -d
//     print only the first of a series of duplicate lines (Default behavior.)
// -u
//     print only the non-duplicate (or “unique”) lines.
// -n

//     for each output line, whether duplicate or unique, prints the source and the line number right before each line. The syntax is as follows, without spaces around the : separators:

//     source : linenum : line

//     Line numbers start from 1. The source is the filename or the string {stdin} if the program is reading from the standard input. 
// filename…
//     read input lines from the given files (instead of standard input). Read all the input files in the order given on the command line.

// You may assume that lines are no longer than 1000 bytes.
// Examples

// Here are some examples. Pay attention to the double backslash sequences. Those certainly work for bash and other Bourne shell-compatible shells, and should work for pretty much every other command shell.

// Here we print only the duplicate lines:

// $ printf ciao\\none\\ntwo\\ntwo\\nciao\\none\\n | ./duplicate_lines
// two

// Here we print the “unique” lines with source and line numbers:

// $ printf ciao\\none\\ntwo\\ntwo\\nciao\\none\\n | ./duplicate_lines -n -u
// {stdin}:1:ciao
// {stdin}:2:one
// {stdin}:5:ciao
// {stdin}:6:one

// And again, only the duplicates, also with line numbers.

// $ printf ciao\\ntwo\\ntwo\\nciao\\n3\\n3\\n3\\n | ./duplicate_lines -n -d
// {stdin}:2:two
// {stdin}:5:3

// Now, write the following text in a file called tests/dups1.in:

// ciao
// one
// two
// two
// ciao
// one

// The following command prints the duplicates in tests/dups1.in with source and line numbers:

// $ ./duplicate_lines -d -n tests/dups1.in 
// tests/dups1.in:3:two




void error(char* info){
    fprintf(stderr,"%s\n",info);
    exit(1);
}

void print_mode_def(const char* filename,int print_count){
    FILE* fp;
    int open=0;
    if(strcmp(filename,"stdin")==0)fp = stdin;
    else {
        fp = fopen(filename,"r");
        open = 1;
    }
    char cur[1000];
    char prev[1000];
    int prev_line_count = 0;
    int in_dup = 0;
    while(fgets(cur,sizeof(cur),fp)){
        if(prev_line_count == 0){
            memcpy(prev,cur,strlen(cur));
            prev[strlen(cur)] = '\0';
            prev_line_count ++;
            continue;
        }
        else {
        if(in_dup == 0){
            if(strcmp(prev,cur)==0)
            {
                in_dup = 1;
                if(print_count == 0)
                printf("%s",prev);
                else if(print_count ==1){
                printf("{%s}:%d:%s",filename,prev_line_count,prev);
                }
            }
                prev_line_count++;
                memcpy(prev,cur,strlen(cur));
                prev[strlen(cur)] = '\0';
            }
            else if(in_dup == 1){
                if(strcmp(prev,cur)!=0){
                    in_dup = 0;
                }
                prev_line_count++;
                memcpy(prev,cur,strlen(cur));
                prev[strlen(cur)] = '\0';
            }
        }
    }
        //handle orphan
        //duplicates doesnt have orphan
    if(open)fclose(fp);
}


void print_mode_u(const char* filename,int print_count){
    FILE* fp;
    int open=0;
    if(strcmp(filename,"stdin")==0)fp = stdin;
    else {
        fp = fopen(filename,"r");
        open = 1;
    }
    char cur[1000];
    int in_dup = 0;
    int prev_line_count = 0;
    char prev[1000];
    while(fgets(cur,sizeof(cur),fp)){
        if(prev_line_count ==0){
            memcpy(prev,cur,strlen(cur));
            prev[strlen(cur)] = '\0';
            prev_line_count ++;
            continue;
        }
        else{
        if(in_dup == 0){
            if(strcmp(prev,cur)!=0){
                if(print_count ==0)printf("%s",prev);
                else if(print_count == 1)printf("{%s}:%d:%s",filename,prev_line_count,prev);
            }
            else if(strcmp(prev,cur)==0)in_dup = 1;
        }
        else if(in_dup == 1){
            if(strcmp(prev,cur)!=0){
                in_dup = 0;
            }
        }
        prev_line_count ++;
        memcpy(prev,cur,strlen(cur));
        prev[strlen(cur)] = '\0';
    }
}
    //handle orphan
    if(in_dup == 0){
        if(print_count ==0)printf("%s",prev);
        else if(print_count ==1) printf("{%s}:%d:%s",filename,prev_line_count,prev);
    }
    if(open)fclose(fp);
}






//int print_unique
//int print_dup
//int print_count
//int def

int main(int argc,char* argv[]){
    if(argc == 1){
        print_mode_def("stdin",0);
    }
    else if(argc>1){
        const char* filename = "stdin";
        int def = 1;
        int print_unique = 0;
        int print_dup = 0;
        int print_count = 0;
        for(int i =1;i<argc;i++){
            if(strncmp(argv[i],"-",1)!=0)filename = argv[i];
            else if(strcmp(argv[i],"-d")==0){
                if(print_dup ==1||print_unique ==1)error("invalid format");
                def = 0;
                print_dup = 1;
            }
            else if(strcmp(argv[i],"-u")==0){
                if(print_dup==1 || print_unique ==1)error("invalid format");
                def = 0;
                print_unique = 1;
            }
            else if(strcmp(argv[i],"-n")==0){
                if(print_count==1)error("invalid format");
                print_count = 1;
            }
        }
        //mode1 def or dup =1
        if(def == 1)print_mode_def(filename,print_count);
        else if(def == 0 && print_dup == 1)print_mode_def(filename,print_count);
        else if(def == 0 && print_unique == 1)print_mode_u(filename,print_count);     
    }
}