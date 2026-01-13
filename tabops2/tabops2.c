#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


static char* def_format = "@a";
static char* def_delim = " \t";
static int MAX_LINE = 1025;

static int stack[100];
static int top = 0;

void stack_push(int number)
{
    if(top>=100)return;
    stack[top++] = number;
}

void stack_calculate(char op)
{
    if(top<2)return;
    int left = stack[top-2];
    int right = stack[top-1];
    if(op == '+')
    {
        top-=2;
        stack[top++] = left+right;

    }
    else if(op == '-')
    {
        top-=2;
        stack[top++] = left-right;
    }
    else if(op=='*')
    {
        top-=2;
        stack[top++] = left*right;
    }
    else if(op=='/')
    {
        top-=2;
        stack[top++] = left/right;
    }
}




int tokenizer(char* line,char** tokens,char* delim)
{
    int count = 0;
    char* token = strtok(line,delim);
    while(token!=NULL)
    {
        tokens[count++] = token;
        token = strtok(NULL,delim);
    }
    return count;
}

int is_small_alpha(char ch)
{
    if(ch>= 'a' && ch<='z')return 1;
    return 0;
}

int is_op(char ch)
{
    return(ch == '+'||ch=='-'||ch=='/'||ch=='*');
}

char* replace_mode(char** tokens,char* format,int count)
{
    format++;//skip '@'
    if(is_small_alpha(*format))
    {
        int index = *format - 'a';
        if(count>index)printf("%s",tokens[index]);
    }
    if(*format)return format+1;
    else return format;
}

char* read_digit(char* format)
{
    int res = *format-'0';
    format++;
    while(*format && isdigit(*format))
    {
        res = res*10 + (*format-'0');
        format ++;
    }
    stack_push(res);
    return format;
}


char* stack_mode(char** tokens,char* format,int count)
{
    format++;
    while(*format && *format!='}')
    {
        if(is_small_alpha(*format))
        {
            int index = *format-'a';
            //if can find, push it
            if(count>index)stack_push(atoi(tokens[index]));
            //if cannot find,push 0
            else if(count<=index)stack_push(0);
            format++;
            continue;
        }
        else if(isdigit(*format))
        {
            format = read_digit(format);
            continue;
        }
        else if(is_op(*format))
        {
            stack_calculate(*format);
            format++;
            continue;
        }
        else
        {
            format++;
            continue;
        }
    }
    if(top>0)
    {
        printf("%d",stack[top-1]);
        top = 0;
    }
    if(*format)return format+1;
    else return format;
}

void print_format(char** tokens,char* format,int count)
{
    while(*format)
    {
        if(*format == '@')
        {
            format = replace_mode(tokens,format,count);
            continue;
        }
        else if(*format == '{')
        {
            format = stack_mode(tokens,format,count);
            continue;
        }
        else
        {
            putchar(*format);
            format++;
            continue;
        }
    }
    putchar('\n');
}

void print(char* format,char* delim,char* filename)
{
    FILE* fp;
    int open_file = 0;
    if(strcmp(filename,"stdin")==0)fp = stdin;
    else
    {
        fp = fopen(filename,"r");
        if(!fp)return;
        open_file = 1;
    }

    char line[MAX_LINE];
    while(fgets(line,sizeof(line),fp))
    {
        char* n_symbol = strchr(line,'\n');
        if(n_symbol)*n_symbol = '\0';
        char* tokens[1000];
        int count = tokenizer(line,tokens,delim);
        if(count ==0)continue;
        print_format(tokens,format,count);
    }
    if(open_file)fclose(fp);
}


int main(int argc,char* argv[])
{
    char* format = def_format;
    char* delim = def_delim;
    if(argc ==1)
    {
        print(format,delim,"stdin");
    }
    else 
    {
        int process =0;
        for(int i =1;i<argc;i++)
        {
            char* eq = strchr(argv[i],'=');
            if(eq)
            {
                if(strncmp(argv[i],"format",6)==0)format = eq+1;
                else if(strncmp(argv[i],"delim",5)==0)delim = eq+1;
            }
            else
            {
                print(format,delim,argv[i]);
                process = 1;
            }
        }
        if(process == 0)print(format,delim,"stdin");
    }
    return 0;
}