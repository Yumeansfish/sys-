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
static char* cur=NULL;

static char* buffer = NULL;
static int buffer_size = 0;
static int buffer_capacity = 0;

void buffer_realloc()
{
    int new_capacity = 0;
    if(buffer_capacity ==0)new_capacity = 100;
    else new_capacity = buffer_capacity*2;
    buffer_capacity = new_capacity;
    char* tmp = realloc(buffer,sizeof(char)*buffer_capacity);
    if(!tmp)exit(EXIT_FAILURE);
    buffer = tmp;
}



void cleanup()
{
    if(table)
    {
        for(int i =0;i<size;i++)
        {
            if(table[i].p)free(table[i].p);
            if(table[i].t)free(table[i].t);
        }
    }
    free(table);
    free(buffer);
}

void error(char* str)
{
    cleanup();
    fprintf(stderr,"%s",str);
    exit(EXIT_FAILURE);
}


void table_realloc()
{
    int new_capacity = 0;
    if(capacity ==0)new_capacity = 100;
    else new_capacity = capacity*2;
    capacity = new_capacity;
    struct mapping* tmp = realloc(table,sizeof(struct mapping)*capacity);
    if(!tmp)exit(EXIT_FAILURE);
    table = tmp;
}

void continue_writing(char* line)
{
    *cur ++ = '\n';
    line++;
    while(*line)
    {
        *cur ++ = *line++;
    }
}

void add_new_mapping(char* line)
{
    char* symbol = strchr(line,':');
    int len = symbol -line;
    if(size>=capacity)table_realloc();
    table[size].p=malloc(len+1);
    memcpy(table[size].p,line,len);
    table[size].p[len] = '\0';
    table[size].t = malloc(200000);
    cur=table[size].t;
    char* read = symbol+1;
    while(*read)
    {
        *cur++ = *read++;
    }
}


void end_writing()
{
    *cur = '\0';
    cur = NULL;
    size++;
}


void get_table(char* filename)
{
    FILE* fp = fopen(filename,"r");
    if(!fp)
    {
        fprintf(stderr,"invalid rules file %s\n",filename);
        exit(EXIT_FAILURE);
    }
    char line[MAX_LINE+1];
    while(fgets(line,sizeof(line),fp))
    {
        //delete \n
        char* n_symbol = strchr(line,'\n');
        *n_symbol = '\0';
        char* symbol = strchr(line,':');
        if(!symbol)continue;

        //different mode

        //when start is :
        if(*line == ':')
        {
            if(cur)continue_writing(line);
            else if(!cur)error("invalid format");
        }

        //when meet :,cur_writing =1;
        else if(*line!=':')
        {
            if(cur)end_writing();
            add_new_mapping(line);
        }
    }
    //handle orphan
    if(cur)end_writing();
    fclose(fp);
}



void write_in_buffer()
{
    int c;
    if(buffer_size>=buffer_capacity)buffer_realloc();
    while((c=getchar())!=EOF)
    {
        if(buffer_size>=buffer_capacity)buffer_realloc();
        buffer[buffer_size++] = c;
        continue;
    }
    buffer[buffer_size] = '\0';
}




void print()
{
    char* read = buffer;
    while(*read)
    {
        int found = 0;
        char* replace = NULL;
        int len = 0;
        for(int i =0;i<size;i++)
        {
            char* p = table[i].p;
            len = strlen(p);
            if(strncmp(p,read,len)==0)
            {
                found = 1;
                replace = table[i].t;
                break;
            }
        }
        if(!found)
        {
            putchar(*read);
            read++;
        }
        else 
        {
            printf("%s",replace);
            read += len;

        }
    }
    return ;
}






int main(int argc,char*argv[])
{
    if(argc==1)
    {
        get_table("RULES");
    }
    else 
    {
        for(int i=1;i<argc;i++)
        {
            get_table(argv[i]);
        }
    }
    write_in_buffer();
    print();
    cleanup();
    return EXIT_SUCCESS;
}




