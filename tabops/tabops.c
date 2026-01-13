#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


static char* def_format = "@a";
static char* def_delim = " \t";
static int MAX_LINE = 1300;


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

char* replace_mode(char** tokens,char* format,int count)
{
    //format++ to see whether is small alpha
    format ++;
    if(!is_small_alpha(*format))return format+1;
    int index = *format - 'a';
    //example, if index = 0,then count should be 1,so count > index
    if(count<=index)return format+1;
    printf("%s",tokens[index]);
    return format+1;
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