#include<string.h>
#include<stdio.h>
#include<stdlib.h>
//requirement

// Tokenize Lines

// Implement the following function. The semantics is identical to that of the strtok function from the C standard library:

// char * string_tokenize(char * str, const char * delim);

// With this function, write a program called line_strings that, for each non-empty string in its standard input, outputs the string preceded by the line number and the sequence number of that string within its line. For example, given the following input:

// one two three
// 1 2 3 4

// 5,6,7 8,9,10

// the program must output:

// 1,1:one
// 1,2:two
// 1,3:three
// 2,1:1
// 2,2:2
// 2,3:3
// 2,4:4
// 4,1:5,6,7
// 4,2:8,9,10

// Thus the strings in the input stream are defined by delimiter characters. The new-line character is always a delimiter, since we are parsing the strings in each line. In the example above, and by default, the delimiters are also the space (' ') and tabulation ('\t') characters.

// The program must also accept an optional commend-line argument that defines the delimiter characters, in addition to the new-line character. For example, with the input given above, the command ./line_strings , must print the following output:

// 1,1:one two three
// 2,1:1 2 3 4
// 4,1:5
// 4,2:6
// 4,3:7 8
// 4,4:9
// 4,5:10



static char* saved_ptr = NULL;
static char* def = " \t\n";
static char delim_buffer[20000];

char* string_tokenize(char*str,const char* delim){
    //first time ,set 
    if(str){
        saved_ptr = str;
    }
    if(!saved_ptr)return NULL;
    while(*saved_ptr && strchr(delim,*saved_ptr))saved_ptr++;
    if(!*saved_ptr)return NULL;
    char* start = saved_ptr;
    while(*saved_ptr){
            if(strchr(delim,*saved_ptr)){
                *saved_ptr++ = '\0';
                return start;
            }
            else saved_ptr ++;
        }
        //handle orphan
    return start;
}




void scan_and_print(int isdef){
    char line[1000];
    char* separators;
    if(isdef)separators = def;
    else separators = delim_buffer;
       

    int line_count = 0;
    int col_count = 1;

    while(fgets(line,sizeof(line),stdin)){
        line_count ++;
        col_count = 1;
        char* token = string_tokenize(line,separators);
        if(token){
            printf("%d,%d:%s\n",line_count,col_count,token);
            col_count ++;
        }
        while(token!=NULL){
            token = string_tokenize(NULL,separators);
            if(token){
                printf("%d,%d:%s\n",line_count,col_count,token);
                col_count++;
            }
        }
}
}



int main(int argc,char* argv[]){
    if(argc == 1){
        scan_and_print(1);
    }
    else{
        int len = strlen(argv[1]);
        memcpy(delim_buffer,argv[1],len);
        delim_buffer[len] = '\n';
        delim_buffer[len+1] = '\0';
        scan_and_print(0);
    }
    return 1;
}





