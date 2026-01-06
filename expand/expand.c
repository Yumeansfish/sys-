#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LINE 2000



// Exercise 52. (90’) In a source file called expand.c or expand.cc, write a C or C++ program that
// copies its standard input to its standard output replacing some strings in the input as specified
// by a set of rules. A rule, denoted p → t, is defined by a pattern strings p and a replacement text
// t, and specifies that every occurrence of pattern p in the input must be replaced with text t in the
// output. For example, with the rule “Hello”→“Ciao” and the input “Hello World!”, the program
// must output “Ciao World!”.
// The program reads a sequence of rules from one or more files. The file names are given as
// command-line arguments. With no arguments, the program reads the default file RULES. A rule
// p → t is written in a file as a line “p:t”. You may assume that lines are at most 2000 characters
// long. A text t that consists of multiple lines continues on multiple lines in the rules file with each
// of the continuing lines starting with a colon. Lines that do not contain a colon character must be
// ignored. See the example below:
// rules file rules
// poem:Tyger Tyger, burning bright,
// :In the forests of the night;
// :What immortal hand or eye,
// :Could frame thy fearful symmetry?
// :
// ciao:hello
// these two lines will be ignored
// the following text is empty
// empty text:
// “poem” → “Tyger Tyger, burning bright,\n
// In the forests of the night;\n
// What immortal hand or eye,\n
// Could frame thy fearful symmetry?\n”
// “ciao” → “hello”
// “empty text” → “”
// Notice that a pattern may not contain any new-line or colon (:) character, and may not be empty.
// Conversely, the replacement text may contain any character, including new-line and colon, and it
// may also be empty.
// Should any error occur while reading a rules file f , the program must print the error message
// “invalid rules file f ” and then terminate immediately with the exit status EXIT_FAILURE. The
// exist status must otherwise be EXIT_SUCCESS. (EXIT_SUCCESS and EXIT_FAILURE are defined in
// stdlib.h.)
// The rules are applied in the order given in the rules files. That is, if multiple rules are applicable
// at any point in the input, the program applies the first applicable rule. For example, with the rules
// “Hello”→“Ciao” and “Hell”→“Inferno” given in this order in a rules file, and with the input
// “Hello darkness, my old friend”, the output must be “Ciao darkness, my old friend”.
// Notice that the input “Hello darkness. . . ” matches the pattern of both rules. Had the rules been
// given in the inverse order, the output would have been “Infernoo darkness, my old friend”.
// The application of rules is mutually exclusive and non-recursive. This means that, when a rule is
// applied to some pattern in the input and therefore that pattern is replaced with the corresponding
// text in the output, neither the pattern nor the replacement text, nor any input before the pattern,
// are considered further for the application of any rule. For example, given the rules “A”→“ASA”,
// “I”→“ISI”, and “SANI”→“”, the input “ANIMA” is transformed into the output “ASANISIMASA”, and
// the input “SANITY” is transformed into “TY”.
// Hint: in C++, the std::ifstream class declared in fstream can be used to read from a file, and a good
// way to read lines is with std::getline declared in string. In C, use fopen (and fclose) and fgets. In
// C++, see std::string and its substr feature. In C, strncmp might be useful for pattern matching.



struct mapping{
    char* p;
    char* t;
};




static struct mapping* table = NULL;
static int size = 0;
static int capacity = 0;
static char* cur_text = NULL;
static char* buffer = NULL;
static int buffer_size = 0;
static int buffer_capacity = 0;


void error(char* info)
{
    fprintf(stderr,"%s\n",info);
    exit(EXIT_FAILURE);
}

void buffer_realloc()
{
    int new_capacity = 0;
    if(buffer_capacity ==0)new_capacity = 1000;
    else new_capacity = buffer_capacity *2;
    buffer_capacity = new_capacity;
    char* tmp = realloc(buffer,buffer_capacity*sizeof(char));
    if(!tmp)error("mem");
    buffer = tmp;
}


void table_realloc()
{
    int new_capacity = 0;
    if(capacity == 0)new_capacity = 100;
    else new_capacity = capacity *2;
    capacity = new_capacity;
    struct mapping* tmp = realloc(table,capacity*sizeof(struct mapping));
    if(!tmp)error("mem");
    table = tmp;
}


int check_symbol(char* line)
{
    while(*line)
    {
        if(*line == ':')return 1;
        line ++;
    }
    return 0;
}

void add_mapping(char* line)
{
    //find first :
    char* fir_symbol = strchr(line,':');
    char* start = line;

    int len = fir_symbol - start;

    //add it to arr
    if(size >= capacity) table_realloc();
    table[size].p = malloc(len+1);
    memcpy(table[size].p,start,len);
    table[size].p[len] = '\0';

    //handle t
    table[size].t = malloc(200000);
    cur_text = table[size].t;

    fir_symbol ++;
    while(*fir_symbol && *fir_symbol != '\n')
    {
        *cur_text++ = *fir_symbol++;
    }
}

void continue_writing(char* line)
{
    *cur_text ++ = '\n';
    line++;
    while(*line && *line !='\n')
    {
        *cur_text++ = *line++;
    }
}

void end_writing()
{
    *cur_text = '\0';
    size++;
    cur_text = NULL;
}



void get_rule(FILE* fp)
{
    char line[MAX_LINE];
    while(fgets(line,sizeof(line),fp))
    {
        //ignore line without :
        if(!check_symbol(line))continue;


        //: is in the start and no cur_text,ignore
        else if(!cur_text && *line == ':')continue;

        //: is in the start and has cur_text;
        else if(cur_text && *line == ':')
        continue_writing(line);

        //: is in the middle and no cur_text,add new map
        else if(!cur_text && *line != ':')
        add_mapping(line);

        //: is in the middle and has cur_text,end wrting
        else if(cur_text && *line != ':')
        {end_writing();
        add_mapping(line);
        }
    }
    //handle orphan
    if(cur_text)
    end_writing();
}


void convert_to_buffer()
{
    int c;
    if(buffer_size>=buffer_capacity)buffer_realloc();
    while((c=getchar())!=EOF)
    {
        if(buffer_size>=buffer_capacity)buffer_realloc();
        buffer[buffer_size++] = c;
        continue;
    }
    buffer[buffer_size]='\0';
}


void print()
{
    convert_to_buffer();
    char* buf = malloc(200000);
    char* write = buf;
    if(!write)error("mem");
    char* read = buffer;
    while(*read)
    {
        int found = 0;
        for(int i =0;i<size;i++)
        {
            int len = strlen(table[i].p);
            if(strncmp(table[i].p,read,len)==0)
            {
                memcpy(write,table[i].t,strlen(table[i].t));
                read += len;
                write += strlen(table[i].t);
                found = 1;
                break;
            }
        }
        if(!found)*write++ = *read++;
    }
    *write = '\0';
    printf("%s",buf);
    free(buf);
}











int main(int argc,char* argv[])
{
    if(argc == 1)
    {
        FILE* fp = fopen("RULES","r");
        if(!fp)
        {
            fprintf(stderr,"invalid rules file RULES\n");
            exit(EXIT_FAILURE);
        }
        get_rule(fp);
        fclose(fp);
    }
    else
    {
        for(int i=1;i<argc;i++)
        {
            FILE* fp = fopen(argv[i],"r");
            if(!fp)
            {
                fprintf(stderr,"invalid rules file %s\n",argv[i]);
                exit(EXIT_FAILURE);

            }
            get_rule(fp);
            fclose(fp);
        }
    }
    print();
    return EXIT_SUCCESS;

}