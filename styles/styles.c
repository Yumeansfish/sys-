#include<stdio.h>
#include<string.h>
#include<stdlib.h>


// Exercise 58. (50’) In a source file called styles.c or styles.cc write a C or C++ program that out-
// puts a set of text styles, each having a name, a foreground color, a background color, and a font
// name. Styles are defined by a specification read from one or more files whose names are passed as
// command-line arguments. When no arguments are given, the specification is read from the stan-
// dard input. The program must output all the styles specified in the input in alphabetical order of
// style name. For example, with the following specification
// style ticino-normal foreground #803333 background blue font fixed
// style ticino-bright foreground #ff background bright-blue font italic
// color bright-blue 0000ff
// color blue 333380
// style default
// the program must then output the following completely specified styles
// default: fg=0,0,0 bg=255,255,255 ft=fixed
// ticino-bright: fg=255,0,0 bg=0,0,255 ft=italic
// ticino-normal: fg=128,51,51 bg=51,51,128 ft=fixed
// The input consists of one-line specifications. A color specification defines a symbolic name for a
// color. The syntax is as follows:
// color ⟨color-name⟩ ⟨color-spec⟩
// A color-name is a string that does not contain any space character. A color-spec is a string that
// defines an RGB color exactly as specified in Exercise 57. (You may well share the same code
// between this and Exercise 57.) For example, input line “color bright−blue 0000ff” defines a color
// named bright-blue whose red, green, and blue components are 0, 0, and 255, respectively. Similarly,
// an input line “color bright−red ff” defines a color with red, green, and blue components 255, 0, 0,
// respectively.
// A style specification defines a style with a given name and any combination of foreground, back-
// ground, and font attributes. The syntax is:
// style ⟨style-name⟩ [ ⟨attribute⟩ ⟨value⟩ ] . . .
// A style-name is a string without spaces. Valid attributes and their values are:
// foreground ( #⟨color-spec⟩ | ⟨color-name⟩ )
// background ( #⟨color-spec⟩ | ⟨color-name⟩ )
// font ⟨font-name⟩
// A font-name is a string without spaces. A color-spec is preceded by a ‘#’ (but no spaces) and has
// the same syntax described above. A color-name must correspond to the name in a color com-
// mand present anywhere in the input. The default foreground color is #000000 (black); The default
// background color is #FFFFFF (white); the default font is fixed.
// The output consists of one line for each style formatted as follows:
// ⟨style-name⟩: fg=⟨byte⟩,⟨byte⟩,⟨byte⟩ bg=⟨byte⟩,⟨byte⟩,⟨byte⟩ ft=⟨font-name⟩
// fg=, bg=, and ft= introduce the foreground color, background color, and font name, respectively.
// The three byte values represent the red, green, and blue components of a color.
// If the input is valid, the program must terminate with the EXIT_SUCCESS status. Otherwise, with
// any error in the input, such as bad format or unknown color names, the program must terminate
// immediately with the EXIT_FAILURE status


void error(char* info)
{
    fprintf(stderr,"%s\n",info);
    exit(EXIT_FAILURE);
}


struct color {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

struct color_def{
    char* name;
    char* value;
};


struct style{
    char* name;
    char* bg_info;
    char* fg_info;
    char* ft_name;
    struct color* bg;
    struct color* fg;
};

struct color_def* color_table = NULL;
static int color_size = 0;
static int color_capacity = 0;

struct style* table = NULL;
static int size = 0;
static int capacity = 0;

static char* def_fg = "#000000";
static char* def_bg = "#FFFFFF";
static char* def_ft = "fixed";
static char* hex = "0123456789abcdefABCDEF";



void table_realloc()
{
    int new_capacity;
    if(capacity == 0)new_capacity = 100;
    else new_capacity = capacity * 2;
    capacity = new_capacity;
    struct style* tmp = realloc(table,capacity*sizeof(struct style));
    if(!tmp)error("mem");
    table = tmp;
}

void color_table_realloc()
{
    int new_capacity;
    if(color_capacity == 0)new_capacity = 100;
    else new_capacity = color_capacity * 2;
    color_capacity = new_capacity;
    struct color_def* tmp = realloc(color_table,color_capacity*sizeof(struct color_def));
    if(!tmp)error("mem");
    color_table = tmp;
}

int tokenizer(char* line,char* tokens[10000])
{
    int style_line = 0;
    int color_line = 0;
    int count = 0;
    char* token = strtok(line," \t\r\n");
    while(token!=NULL)
    {
        tokens[count++] = token;
        token = strtok(NULL," \t\r\n");
    }
    if(count ==0)return 0;
    if(strcmp(tokens[0],"color")==0)color_line = 1;
    else if(strcmp(tokens[0],"style")==0)style_line =1;
    else 
    {
        error("invalid format");
        return -1;
    }

    if(color_line ==1 && count!=3)error("invalid format");
    else if(style_line && count%2 != 0)error("inavlid format");
    return count;
}



void get_table(char* filename)
{
    FILE* fp;
    if(filename)
    {
        fp = fopen(filename,"r");
        if(!fp)error("invalid file");
    }
    else fp = stdin;
    char line[1000];

    static struct style* cur_style = NULL;
    while(fgets(line,sizeof(line),fp))
    {
        char* tokens[10000];
        int count = tokenizer(line,tokens);
        if(count ==0)continue;

        //format
        //token[0]:style
        //token[1]:name
        //token[2]:fg
        //token[3]:fg_needed
        //4:bg
        //5:bg_needed
        //6:font
        //7:font_needed


        //store the bg and fg info in it if exist.
        if(count%2 ==0)
        {
            if(size>=capacity)table_realloc();
            int len = strlen(tokens[1]);
            table[size].name = malloc(len+1);
            memcpy(table[size].name,tokens[1],len);
            table[size].name[len] = '\0';
            cur_style = &table[size];
            size++;
            for(int i =2;i<count;i+=2)
            {
                if(strcmp(tokens[i],"foreground")==0)
                {
                    int len = strlen(tokens[i+1]);
                    cur_style->fg_info = malloc(len+1);
                    memcpy(cur_style->fg_info,tokens[i+1],len);
                    cur_style->fg_info[len] = '\0';
                }
                else if(strcmp(tokens[i],"background")==0)
                {
                    int len = strlen(tokens[i+1]);
                    cur_style->bg_info = malloc(len+1);
                    memcpy(cur_style->bg_info,tokens[i+1],len);
                    cur_style->bg_info[len] = '\0';
                }
                else if(strcmp(tokens[i],"font")==0)
                {
                    int len = strlen(tokens[i+1]);
                    cur_style->ft_name = malloc(len+1);
                    memcpy(cur_style->ft_name,tokens[i+1],len);
                    cur_style->ft_name[len] = '\0';
                }
                else error("invalid format");
            }
        }

        //if count == 3 then its color
        //format
        //token 0 = color
        //token 1 = color-name
        //token 2 = color-info
        if(count ==3)
        {
            if(color_size>=color_capacity)color_table_realloc();
            int len = strlen(tokens[1]);
            color_table[color_size].name = malloc(len+1);
            memcpy(color_table[color_size].name,tokens[1],len);
            color_table[color_size].name[len] = '\0';

            int len_info = strlen(tokens[2]);
            color_table[color_size].value = malloc(len_info+1);
            memcpy(color_table[color_size].value,tokens[2],len_info);
            color_table[color_size].value[len_info] = '\0';
            color_size++;     
        }
    }
}


int hex_value(char ch)
{
    if(ch>='0' && ch<='9')return ch-'0';
    if(ch>='a'&&ch<='z')return ch-'a'+10;
    if(ch>='A'&&ch<='Z')return ch-'A'+10;
    else{
        error("invalid format");
        return -1;
    }
}

void string_to_color(struct color* c,char* str)
{
    int value[6];
    int count = 0;
    if(*str == '#')str++;
    while(*str && count<=5 && strchr(hex,*str))
    {
        value[count++] = hex_value(*str);
        str++;
    }
    int diff = 6 - count;
    while(diff)
    {
        value[count++] = hex_value('0');
        diff--;
    }
    c->red = 16*value[0] + value[1];
    c->green = 16*value[2] + value[3];
    c->blue = 16*value[4] + value[5];
}

void replace_color()
{
    int found = 0;
    for(int i =0;i<size;i++)
    {
        if(table[i].bg_info && table[i].bg_info[0] !='#')
        {
            found = 0;
            for(int j =0;j<color_size;j++)
            {
                if(strcmp(table[i].bg_info,color_table[j].name)==0)
                {
                    table[i].bg_info = color_table[j].value;
                    found = 1;
                }
            }
            if(!found)error("invalid format");
        }
        if(table[i].fg_info && table[i].fg_info[0] !='#')
        {
            found = 0;
            for(int j =0;j<color_size;j++)
            {
                if(strcmp(table[i].fg_info,color_table[j].name)==0)
                {
                    table[i].fg_info = color_table[j].value;
                    found = 1;
                }
            }
            if(!found)error("invalid format");
        }
}
}



void calculate_color()
{
    for(int i =0;i<size;i++)
    {
        table[i].bg = malloc(sizeof(struct color));
        table[i].fg = malloc(sizeof(struct color));
        if(!table[i].bg||!table[i].fg)error("mem");
        if(!table[i].bg_info)table[i].bg_info = def_bg;
        if(!table[i].fg_info)table[i].fg_info = def_fg;
        if(!table[i].ft_name)table[i].ft_name = def_ft;
        string_to_color(table[i].bg,table[i].bg_info);
        string_to_color(table[i].fg,table[i].fg_info);
    }
}

void print()
{
    for(int i =0;i<size;i++)
    {
        printf
        ("%s: fg=%d,%d,%d bg=%d,%d,%d ft=%s\n", 
            table[i].name,
            table[i].fg->red,
            table[i].fg->green,
            table[i].fg->blue,
            table[i].bg->red,
            table[i].bg->green,
            table[i].bg->blue,
            table[i].ft_name
        );

    }
}

int compare_func(const void* a,const void* b)
{
    const struct style* sa = (const struct style*)a;
    const struct style* sb = (const struct style*)b;
    return strcmp(sa->name,sb->name);
}



int main(int argc,char* argv[])
{
    if(argc ==1)
    {
        get_table(NULL);
        replace_color();
        calculate_color();
        qsort(table,size,sizeof(struct style),compare_func);
        print();
    }
    else
    {
        for(int i =1;i<argc;i++)
        {
            get_table(argv[i]);
            
        }
        replace_color();
        calculate_color();
        qsort(table,size,sizeof(struct style),compare_func);
        print();
    }
}