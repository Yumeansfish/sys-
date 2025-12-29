#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


struct ch_info{
    char ch;
    struct mapping* head;
};

struct mapping{
    char ch;
    int feq;
    struct mapping* next;
};


static struct ch_info* ch_info_table = NULL;
static int capacity = 0;
static int size = 0;

static char buffer[100000];
static char* write = buffer;

void write_to_buffer(){
    int c;
    while((c=getchar())!=EOF){
        if(isalpha((unsigned char)c)){
        *write ++ = toupper(c);
        continue;
        }
        else {
            *write ++ = c;
            continue;
        }
    }
    *write = '\0';
}

void ch_info_table_realloc(){
    int new_capacity = 0;
    if(capacity ==0)new_capacity =100;
    else new_capacity = capacity * 2;
    capacity = new_capacity;
    struct ch_info* tmp = realloc(ch_info_table,sizeof(struct ch_info)*capacity);
    if(!tmp)return;
    ch_info_table = tmp;
}

struct ch_info* find_helper(char fir){
    for(int i =0;i<size;i++){
        if(ch_info_table[i].ch == fir)return &ch_info_table[i];
    }
    return NULL;
}

struct mapping* find_helper_mp(struct ch_info* info,char sec){
    if(!info->head)return NULL;
    struct mapping* itr = info->head;
    while(itr){
        if(itr->ch == sec)return itr;
        itr = itr->next;
    }
    return NULL;
}



void read_buffer(){
    char * read= buffer;
    while(*read&&*(read+1)){
        if(!isalpha(*read) || !isalpha(*(read+1))){
            read++;
            continue;
        }
        char fir = *read;
        char sec = *(read+1);
        //first find fir in ch_info_table
        struct ch_info* target = find_helper(fir);
        //if found, find sec
        if(target){
            //find sec
            struct mapping* mp = find_helper_mp(target,sec);
            //if found,add feq
            if(mp) mp->feq++;
            //if not found, head insert
            if(!mp){
                struct mapping* new_mp = malloc(sizeof(struct mapping));
                if(!new_mp)return;
                new_mp -> ch = sec;
                new_mp -> feq = 1;
                new_mp -> next = target -> head;
                target->head = new_mp;
            }
        }

        //not find target
        else if(!target){
            struct ch_info* new_ch_info = malloc(sizeof(struct ch_info));
            if(!new_ch_info)return;
            new_ch_info -> ch = fir;
            new_ch_info -> head = NULL;
            struct mapping* new_mp = malloc(sizeof(struct mapping));
            if(!new_mp)return;
            new_mp -> ch = sec;
            new_mp->feq = 1;
            new_mp->next = new_ch_info -> head;
            new_ch_info->head = new_mp;
            //add it on arr
            if(size >= capacity)ch_info_table_realloc();
            ch_info_table[size] = *new_ch_info;
            size ++;
            free(new_ch_info);
        }
        read++;
    }
}


void get_table(){
    write_to_buffer();
    read_buffer();
}



void print(){
    for(int i =0;i<size;i++){
        struct ch_info cur = ch_info_table[i];
        if(!cur.head)continue;//skip if no mapping

        //find the most frequent sec char
        int max_feq = 0;
        char res = 'a';
        struct mapping* itr = cur.head;
        while(itr){
            if(itr->feq > max_feq){
                max_feq = itr->feq;
                res = itr->ch;
            }
            else if(itr->feq == max_feq && itr->ch < res){
                res = itr->ch;
            }
            itr = itr->next;
        }
        printf("%c%c\n",cur.ch,res);
    }
}


int compare_ch(const void *a, const void *b){
    const struct ch_info *ch_a = (const struct ch_info*)a;
    const struct ch_info *ch_b = (const struct ch_info*)b;

    return ch_a->ch - ch_b ->ch;

}


int main(int argc,char* argv[]){
    get_table();
    qsort(ch_info_table,size,sizeof(struct ch_info),compare_ch);
    print();
}
