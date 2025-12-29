#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LINE 2000


void error(char* str){
    fprintf(stderr,"%s\n",str);
    exit(EXIT_FAILURE);
}


struct mapping{
    char* p;
    char* t;
};

static struct mapping* mapping_table = NULL;
static int capacity = 0;
static int size = 0;

static struct mapping* cur_mapping = NULL;
static char* write = NULL;

static char input_buffer[1000000];
static char* write_buffer = input_buffer;

//search whether p exist
int find_helper(char* p){
    if(!p)return 0;
    for(int i =0;i<size;i++){
        if(strcmp(mapping_table[i].p,p)==0)return 1;
    }
    return 0;
}


int check_symbol(char* line){
    //review strchr,is this correct way to use it ?
    return strchr(line,':') != NULL;
}

void mapping_table_realloc(){
    int new_capacity;
    if(capacity == 0 )new_capacity = 100;
    else new_capacity = capacity * 2;
    capacity = new_capacity;
    struct mapping* tmp = realloc(mapping_table,sizeof(struct mapping)*capacity);
    if(!tmp)error("mem");
    mapping_table = tmp;
}


void add_mapping(char* line){
    char* start = line;
    while(*line){
        if(*line == ':')break;
        line++;
    }
    int len = line - start;
    if(len==0)error("invalid file");
    

    //create new struct
    struct mapping* new = malloc(sizeof(struct mapping));
    if(!new)return error("mem");
    new->p = malloc(len+1);
    if(!new->p)return error("mem");
    memcpy(new->p,start,len);
    new->p[len] = '\0';
    
    //check whether exist
    if(find_helper(new->p)){
        free(new->p);
        free(new);
        return;
    }

    new->t = malloc(200000000);
    if(!new->t)return error("mem");
    //copy the remaining t part in this line
    line ++;
    char* middle = line;
    while(*line){
        if(*line == '\n')break;
        line++;
    }
    int len_2 = line - middle;
    memcpy(new->t,middle,len_2);


    //add it to mapping_table;
    if(size >= capacity)mapping_table_realloc();
    mapping_table[size++] = *new;
    free(new);
    

    //cur_mapping and write
    cur_mapping = &mapping_table[size-1];
    write = cur_mapping->t;
    write += len_2;
}


//this is the write when line start with :
//we write \n manaully and skip the \n in the end
void write_replacement(char* line){
    *write ++ = '\n';
    line ++;//skip the first :
    while(*line){
        if(*line == '\n'){
            line++;
            continue;
        }
        *write++ = *line ++;
    }
}

//add '\0' in the end and reset the global ptr
void finish_write(){
    *write = '\0';
    cur_mapping = NULL;
    write = NULL;
}


void get_mapping(FILE* fp){
    char line[MAX_LINE];
    while(fgets(line,sizeof(line),fp))
    {
        //if no : ,skip
        if(!check_symbol(line))continue;
        //if start with : 
        if(*line == ':'){
            if(!cur_mapping)error("invalid format");
            write_replacement(line);
        }
        //if in middle
        else {
            if(!cur_mapping)add_mapping(line);
            else{
                finish_write();
                add_mapping(line);
            }
        }
    }
    //handle orphan
    if(cur_mapping && write)finish_write();

        
}

void convert_to_buffer(){
    int c;
    while((c = getchar())!=EOF){
        *write_buffer++ = c;
        continue;
    }
    *write_buffer = '\0';
}



void print(){
    convert_to_buffer();
    char* read = input_buffer;
    while(*read){
        int found = 0;
        for(int i =0;i<size;i++){
            char* p = mapping_table[i].p;
            int len = strlen(p);
            if(strncmp(p,read,len)==0){
                printf("%s",mapping_table[i].t);
                read += len;
                found = 1;
                break;
            }
        }
        if(!found){
            putchar(*read);
            read++;
        }
        
    }
}



int main(int argc,char* argv[]){
    if(argc == 1){
        FILE* fp = fopen("RULES","r");
        if(!fp)error("invalid rules file RULES");
        get_mapping(fp);
        print();
        fclose(fp);
    }
    else if(argc >= 2){
        for(int i =1;i<argc;i++){
            FILE* fp = fopen(argv[i],"r");
            if(!fp)error("invalid rules file");
            get_mapping(fp);
            fclose(fp);
        }
        print();
    }

}