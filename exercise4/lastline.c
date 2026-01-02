#include<stdio.h>
#include<string.h>
#include<stdlib.h>


static int def_k = 5;

// Last Lines

// Write a program called last_lines that copies on its standard output the last
// lines of its standard input. The value of can be specified as a command-line argument, but it must not be greater than 100 or less than 1. The default is . You may assume that input lines are at most 1000 bytes long including the end-of-line character. 



void print(int k){
    char line[1000];
    char buffer[k][1000];
    int line_count = 0;
    while(fgets(line,sizeof(line),stdin)){
        int len = strlen(line);
        memcpy(buffer[line_count%k],line,len);
        buffer[line_count%k][len] = '\0';
        line_count++;
    }
    if(line_count <k){
        for(int i=0;i<line_count;i++){
            printf("%s",buffer[i]);
        }
    }
    else{
    for(int i=(line_count-k)%k;i<k;i++){
        printf("%s",buffer[i]);
    }
    for(int i=0;i<(line_count-k)%k;i++){
        printf("%s",buffer[i]);
    }
}
}


//0,1,2,3,4,5,6,7 k=5
//3,4,5,6,7
//0,1,2,3,4,0,1,2

//0,1,2,3,4,5,6,7,8,9,10,11,12 k=5
//8,9,10,11,12
//0,1,2,3,4,0,1,2,3,4,0,1,2
//line_count - k = 8




int main(int argc,char* argv[]){
    int k;
    if(argc == 1)k = def_k;
    if(argc>1)k = atoi(argv[1]);
    if(k>100 || k<1){
        fprintf(stderr,"invalid k");
        exit(1);
    }
    print(k);
}