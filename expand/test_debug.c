#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LINE 2000

struct mapping{
    char* p;
    char* t;
};

static struct mapping* table = NULL;
static int size = 0;
static int capacity = 0;
static char* cur_text = NULL;

void error(char* info) {
    fprintf(stderr,"%s\n",info);
    exit(EXIT_FAILURE);
}

void table_realloc() {
    int new_capacity = capacity == 0 ? 100 : capacity * 2;
    capacity = new_capacity;
    struct mapping* tmp = realloc(table, capacity * sizeof(struct mapping));
    if(!tmp) error("mem");
    table = tmp;
}

int check_symbol(char* line) {
    while(*line) {
        if(*line == ':') return 1;
        line++;
    }
    return 0;
}

void add_mapping(char* line) {
    char* fir_symbol = strchr(line,':');
    char* start = line;
    int len = fir_symbol - start;
    
    if(size >= capacity) table_realloc();
    table[size].p = malloc(len+1);
    memcpy(table[size].p,start,len);
    table[size].p[len] = '\0';
    
    table[size].t = malloc(20000);
    cur_text = table[size].t;
    
    fir_symbol++;
    while(*fir_symbol && *fir_symbol != '\n') {
        *cur_text++ = *fir_symbol++;
    }
    
    fprintf(stderr, "DEBUG: Added rule '%s', cur_text offset=%ld\n", 
            table[size].p, cur_text - table[size].t);
}

void continue_writing(char* line) {
    fprintf(stderr, "DEBUG: continue_writing, line=[%s]\n", line);
    *cur_text++ = '\n';
    line++;
    while(*line && *line !='\n') {
        *cur_text++ = *line++;
    }
    fprintf(stderr, "DEBUG: after continue_writing, cur_text offset=%ld\n", 
            cur_text - table[size].t);
}

void end_writing() {
    *cur_text = '\0';
    fprintf(stderr, "DEBUG: end_writing, final text length=%zu\n", strlen(table[size].t));
    size++;
    cur_text = NULL;
}

void get_rule(FILE* fp) {
    char line[MAX_LINE];
    while(fgets(line,sizeof(line),fp)) {
        if(!check_symbol(line)) continue;
        if(!cur_text && *line == ':') continue;
        if(cur_text && *line == ':')
            continue_writing(line);
        if(!cur_text && *line != ':')
            add_mapping(line);
        if(cur_text && *line != ':') {
            end_writing();
            add_mapping(line);
        }
    }
    if(cur_text)
        end_writing();
}

int main() {
    FILE* fp = fopen("tests/poem_rules.txt", "r");
    if(!fp) {
        fprintf(stderr, "Can't open file\n");
        return 1;
    }
    get_rule(fp);
    fclose(fp);
    
    printf("\n=== Total rules: %d ===\n\n", size);
    for(int i = 0; i < size; i++) {
        printf("Rule %d:\n", i);
        printf("  Pattern: [%s]\n", table[i].p);
        printf("  Text length: %zu\n", strlen(table[i].t));
        printf("  Text with visible \\n:\n  [");
        for(char* p = table[i].t; *p; p++) {
            if(*p == '\n') printf("\\n");
            else printf("%c", *p);
        }
        printf("]\n\n");
    }
    return 0;
}
