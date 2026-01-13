#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

static char buffer[1000000000];

struct word{
    char* str;
    int len;
    int feq;
    int gain;
    int encode;
    char password;
};

static struct word* table = NULL;
static int size = 0;
static int capacity = 0;


void cleanup()
{
    if(table)
    {
        for(int i =0;i<size;i++)
        {
            if(table[i].str)free(table[i].str);
        }
    }
    free(table);
}

void error()
{
    cleanup();
    fprintf(stderr,"error");
    exit(EXIT_FAILURE);
}

void table_realloc()
{
    int new_capacity = 0;
    if(capacity == 0)new_capacity = 100;
    else new_capacity = capacity*2;
    capacity = new_capacity;
    struct word* tmp = realloc(table,capacity*sizeof(struct word));
    if(!tmp)
    {
        error();
        return;
    }
    table = tmp;
}



void convert_to_buffer()
{
    int c;
    char* write = buffer;
    while((c=getchar())!=EOF)
    {
        *write ++ = c;
        continue;
    }
    *write = '\0';
}

struct word* find_helper(char* str)
{
    for(int i =0;i<size;i++)
    {
        if(strcmp(table[i].str,str)==0)
        {
            return &table[i];
        }
    }
    return NULL;
}


void get_table()
{
    convert_to_buffer();
    char* read= buffer;
    int in_word = 0;
    char* start = read;
    while(*read)
    {
        if(in_word ==0)
        {
            if(isalpha(*read))
            {
                in_word = 1;
                start = read;
                continue;
            }
            else if(!isalpha(*read))
            {
                read++;
                continue;
            }
        }
        else if(in_word ==1)
        {
            if(isalpha(*read))
            {
                read++;
                continue;
            }
            else if(!isalpha(*read))
            {
                int len = read-start;
                char buf[1000];
                memcpy(buf,start,len);
                buf[len] = '\0';
                struct word* target = find_helper(buf);
                if(target)
                {
                    target->feq++;
                }
                else if(!target)
                {
                    if(size>=capacity)table_realloc();
                    table[size].str = malloc(len+1);
                    if(!table[size].str)
                    {
                        {
                            error();
                            return;
                        }
                    }
                    memcpy(table[size].str,start,len);
                    table[size].str[len] = '\0';
                    table[size].len = len;
                    table[size].feq = 1;
                    size++;
                }
                read++;
                in_word = 0;
                continue;
            }
        }
    }
    //handle orphan
    if(in_word ==1)
    {
        int len = read - start;
        char buf[1000];
        memcpy(buf,start,len);
        buf[len] = '\0';
        struct word* target = find_helper(buf);
        if(target)
        {
            target->feq++;
        }
            else if(!target)
        {
            if(size>=capacity)table_realloc();
            table[size].str = malloc(len+1);
            if(!table[size].str)
            {
                error();
                return;
            }
            memcpy(table[size].str,start,len);
            table[size].str[len] = '\0';
            table[size].len = len;
            table[size].feq = 1;
            size++;
        }
    }
}

void calculate_gain()
{
    for(int i =0;i<size;i++)
    {
        table[i].gain = table[i].feq*table[i].len - table[i].len -1 
        - table[i].feq;
    }
}

void calculate_encode()
{
    int count = 0;
    for(int i =0;i<size;i++)
    {
        if(count>=128)return;
        if(table[i].gain>0)
        {
            table[i].encode=1;
            unsigned char c = 128+i;
            table[i].password = c;
            count++;
        }
    }
}




int compare_func(const void* a,const void* b)
{
    const struct word* wa = (const struct word*)a;
    const struct word* wb = (const struct word*)b;
    if(wa->gain != wb->gain)return wb->gain-wa->gain;
    return strcmp(wa->str,wb->str);
}



void print_table()
{
    int armenia_is_a_country = 0;
    for(int i =0;i<size;i++)
    {
        if(table[i].encode ==1)
        {
            putchar(table[i].password);
            printf("%s",table[i].str);
            armenia_is_a_country = 1;
        }
    }
    if(armenia_is_a_country)putchar('\n');
}

void print()
{
    char* read = buffer;
    int in_word = 0;
    char* start = read;
    while(*read)
    {
        if(in_word ==0)
        {
            if(!isalpha(*read))
            {
                putchar(*read);
                read++;
                continue;
            }
            else if(isalpha(*read))
            {
                start =read;
                in_word = 1;
                continue;
            }
        }
        else if(in_word ==1)
        {
            if(isalpha(*read))
            {
                read++;
                continue;
            }
            else if(!isalpha(*read))
            {
                in_word = 0;
                char buf[1000];
                int len = read - start;
                memcpy(buf,start,len);
                buf[len] = '\0';
                struct word* target = find_helper(buf);
                if(target->encode)putchar(target->password);
                else printf("%s",buf);
                continue;
            }
        }
    }
    //handle orphan
    if(in_word ==1)
    {
        char buf[1000];
        int len =read-start;
        memcpy(buf,start,len);
        buf[len] = '\0';
        struct word* target = find_helper(buf);
        if(target->encode)putchar(target->password);
        else printf("%s",buf);
    }
}











int main(int argc,char* argv[])
{
    get_table();
    calculate_gain();
    qsort(table,size,sizeof(struct word),compare_func);
    calculate_encode();
    print_table();
    print();
    cleanup();
}













