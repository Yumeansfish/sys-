#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

// Exercise 65. (60’) Write a C program in a source file named tabops.c that reads data from one or
// more files or from standard input if no files are specified. The program interprets each input line
// as a sequence of data items based on a given set of delimiter characters. The program then writes
// on standard output those data items based on a given format string.
// The delimiters, the format string, and the input files are specified through command-line argu-
// ments. Specifically, format=format-string sets the format string; delim=delimiters sets the de-
// limiters; and any other command-line argument is interpreted as an input file name, which the
// program reads and processes according to the current format and delimiters.
// By default, the format string is “@a” and the delimiters are “ \t”. If no input file names are given,
// the program reads from standard input. For example, consider the following command line:
// ./tabops f1 format=@b,@a f2 delim=/ format=@c f3 f4
// Here, the program reads and processes file f1 with the default format and delimiters, then pro-
// cesses f2 with the format “@b,@a” and default delimiters, and then processes f3 and f4 with format
// “@c” and delimiters “/”.
// The input is read line by line. A line, at most 1024 characters, is interpreted as a sequence of
// data items separated by one or more delimiter characters. The end-of-line character is not consid-
// ered part of the line and therefore of any data item. For example, with delimiters “,.;”, the line
// “Apples,;5;3” is parsed into three items: Apples, 5, and 3.
// For each line, the program outputs the format string where placeholders like @a, @b, etc., are
// replaced with corresponding data items from the line based on alphabetical order (@a for the first
// item, @b for the second, etc.). For example, given the line Apples,5,3 with delimiters "," and the
// format string “@b,@a”, the program outputs 5,Apples.
// A placeholder @x referring to a non-existent data item or where x is any character other than a
// lowercase letter (a–z) is ignored. For instance, if there are three items Apples, 5, 3 and the format
// string is “@b@,@a--@x”, the output will be 5Apples--




static char* def_delim = " \t";
static char* def_format = "@a";


void error(char* info)
{
    fprintf(stderr,"%s\n",info);
    exit(1);
}



int tokenizer(char** tokens,char* line,char* delim)
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

int small_alpha(char ch)
{
    if(ch>='a' && ch<='z')return 1;
    return 0;
}


void print(FILE* fp,char* delim,char* format)
{
    char line[1025];
    while(fgets(line,sizeof(line),fp))
    {
        line[strcspn(line,"\n")] = '\0';
        char* tokens[1000];
        int count = tokenizer(tokens,line,delim);
        //skip empty line
        if(count==0)continue;
        char buffer[1025];
        char* write = buffer;
        char* read = format;
        while(*read)
        {
            if(*read == '@')
            {
                //ignore if x not small alpha
                if(!small_alpha(*(read+1)))
                {
                    read+=2;
                    continue;
                }
                int index = *(read+1)-'a';
                //ignore if cannot find
                //example
                //index = 0;
                //we need count = 1
                //so count >= index +1 valid
                if(count<=index)
                {
                    read+=2;
                    continue;
                }
                int len = strlen(tokens[index]);
                memcpy(write,tokens[index],len);
                write += len;
                read+=2;
            }
            else
            {
                *write ++ = *read++;
            }
        }
        *write = '\0';
        printf("%s\n",buffer);
    }
}











int main(int argc,char* argv[])
{
    FILE* fp;
    char* delim = NULL;
    char* format = NULL;
    if(argc == 1)
    {
        fp = stdin;
        delim = def_delim;
        format = def_format;
        print(fp,delim,format);
        fclose(fp);
    }
    else
    {
        fp = stdin;
        delim = def_delim;
        format = def_format;
        int process = 0;
        for(int i =1;i<argc;i++)
        {
            if(strncmp(argv[i],"format",6)==0)
            {
                format = strchr(argv[i],'=')+1;
            }
            else if(strncmp(argv[i],"delim",5)==0)
            {
                delim = strchr(argv[i],'=')+1;
            }
            else
            {
                fp = fopen(argv[i],"r");
                if(!fp)error("invalid file name");
                print(fp,delim,format);
                process = 1;
                fclose(fp);
            }
        }
        if(!process)
        {
            print(fp,delim,format);
        }
    }
}