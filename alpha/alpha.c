#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


static char* buffer= NULL;
static int size = 0;
static int capacity = 0;

void buffer_realloc()
{
    int new_capacity = 0;
    if(capacity==0)new_capacity =1000;
    else new_capacity = capacity*2;
    capacity = new_capacity;
    char* tmp = realloc(buffer,sizeof(char)*capacity);
    if(!tmp)exit(EXIT_FAILURE);
    buffer=tmp;
}


void encode()
{
    int c;
    int count = 0;
    int write = 0;
    while((c=getchar())!=EOF)
    {
        write = 1;
        if(isalpha((unsigned char)c) && c!='Q')
        {
            putchar(c);
            count++;
            if(count && count % 80 ==0)putchar('\n');
            continue;
        }
        else if(c == 'Q')
        {
            putchar('Q');
            count++;
            if(count && count % 80 ==0)putchar('\n');
            putchar('Q');
            count++;
            if(count && count % 80 ==0)putchar('\n');
            continue;
        }
        else
        {
            unsigned char b = c;
            unsigned char high = (b/16)+'a';
            unsigned char low = (b%16)+'a';
            putchar('Q');
            count++;
            if(count && count % 80 ==0)putchar('\n');
            putchar(high);
            count++;
            if(count && count % 80 ==0)putchar('\n');
            putchar(low);
            count++;
            if(count && count % 80 ==0)putchar('\n');
            continue;
        }
    }
    if(write)putchar('\n');
}


void write_in_buffer()
{
    int c;
    if(size>=capacity)buffer_realloc();
    while((c=getchar())!=EOF)
    {
        if(size>=capacity)buffer_realloc();
        buffer[size++] = c;
        continue;
    }
    buffer[size] = '\0';
}

char* skip_until_alpha(char* read)
{
    while(*read)
    {
        if(!isalpha((unsigned char)*read))read++;
        else break;
    }
    return read;
}


void decode()
{
    char* read = buffer;
    while(*read)
    {
        if(!isalpha((unsigned char)*read))read++;
        else if(isalpha((unsigned char)*read) && *read!='Q')
        {
            putchar(*read);
            read++;
        }
        else if(*read == 'Q')
        {
            read++;
            if(!*read)
            {
                exit(EXIT_FAILURE);
                return;
            }
            read = skip_until_alpha(read);
            if(*read =='Q')
            {
                putchar('Q');
                read++;
                continue;
            }
            else
            {
            //store the current read(first)
            unsigned char fir = *read;
            read++;
            if(!*read)
            {
                exit(EXIT_FAILURE);
                return;
            }
            read = skip_until_alpha(read);
            unsigned char sec = *read;
            //formula
            //fir = x/16+'a'
            //sec = x%16+'a'
            unsigned char origin = (fir-'a')*16 + (sec-'a');
            putchar(origin);
            read++;
            continue;
            }
        }
    }
}

void cleanup()
{
    if(buffer)free(buffer);
}



int main(int argc,char* argv[])
{
    if(argc ==1)
    {
        encode();
    }
    else
    {
        if(strcmp(argv[1],"-d")!=0)
        {
            exit(EXIT_FAILURE);
            return(EXIT_FAILURE);
        }
        write_in_buffer();
        decode();
    }
    cleanup();
    return 0;
}


