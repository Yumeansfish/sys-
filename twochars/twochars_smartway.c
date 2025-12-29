#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


//feq[1][1] = feq of "ab"
static int feq[26][26] = {0};


void get_feq(){
    int c;
    int prev = -1;
    while((c=getchar())!=EOF){
        if(!isalpha((unsigned char)prev)||!isalpha((unsigned char)c)){
        prev =c;
        continue;
        }
        else{
            int fir = toupper(prev) - 'A';
            int sec = toupper(c) - 'A';
            feq[fir][sec] ++;
            prev = c;
            continue;
        }
    }
}

void print(){
    for(int i=0;i<26;i++){
        char fir = 'A' + i;
        int max_feq = 0;
        char res = 'Z'+1;
        for(int j=0;j<26;j++){
            if(feq[i][j]>max_feq){
                max_feq = feq[i][j];
                res = 'A' + j;
            } 
            else if(feq[i][j]==max_feq && ('A'+j - res)<0){
                res = 'A' + j;

            }
        }
        if(max_feq == 0)continue;
        else{
            printf("%c%c\n",fir,res);
        }
    }
}






int main(int argc,char* argv[]){
    get_feq();
    print();
}
