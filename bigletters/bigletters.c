#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

// **
// * *
// **** *** *** ***
// * * * * * * * *
// * * *** *** r o *** r i a t e
// * * *
// When printing an input line, which you may assume is no more than 1000 characters long, the
// corresponding output characters in big letters must be separated horizontally by one space, as in
// the examples above. The total height of the big-letter output corresponding to one input line is
// a fixed number of lines that does not depend on the content of the line, and instead depends on
// the font, as we detail below. Furthermore, there is always an empty line separating the big-letter
// output of two consecutive input lines.
// The height of the output of a single input line is the maximal height above the baseline of any
// character, plus the maximal depth of any character. More specifically, for each big-letter character
// with height h and depth d, including the default ones, let h∗ = h − d be the height of the character
// above the baseline, and let H∗ and D be the maximal values of h∗ and d over all characters. Then,
// a single non-empty input line results in an output of exactly H∗ + D lines. So, again with a font
// file consisting of the two examples above, the two consecutive input lines “Appropriate” and
// “power to the people” must be printed as follows. The symbol “|” explicitly indicates the end
// of each output line.
// ** |
// ←− 6 lines for the first input line
// * *|
// **** *** *** *** |
// * * * * * * * *|
// * * *** *** r o *** r i a t e|
// * * * |
// | ←− empty, separation line
// |
// ←− 6 lines for the second input line
// |
// *** *** *** |
// * * * * * *|
// *** o w e r t o t h e *** e o *** l e|
// * * * |
// Notice that each input line results in six lines of output. This is because the maximal height above
// the baseline is 5 (character “A”) and the maximal depth is 1 (character “p”). Then, an additional
// empty line separates those two groups of six output lines. Notice also that all output lines must
// terminate at the end of the right-most big-letter character matrix that occupies that line.





struct mapping{
    char ch;
    int width;
    int height;
    int depth;
    char* content;
};


static struct mapping* table = NULL;
static int size = 0;
static int capacity = 0;
static int error = 0;

void cleanup()
{
    if(table)
    {
        for(int i =0;i<size;i++)
        {
            if(table[i].content)free(table[i].content);
        }
        free(table);
    }
}


void table_realloc()
{
    int new_capacity = 0;
    if(capacity ==0)new_capacity = 100;
    else new_capacity = capacity * 2;
    capacity = new_capacity;
    struct mapping* tmp = realloc(table,capacity*sizeof(struct mapping));
    if(!tmp)return ;
    table = tmp;
}

int tokenizer(char* str,char** tokens)
{
    int count =0;
    char* token = strtok(str," ");
    while(token!=NULL)
    {
        tokens[count++] = token;
        token = strtok(NULL," ");
    }
    return count;
}

int is_number(char* str)
{
    while(*str)
    {
        if(!isdigit(*str))return 0;
        str++;
    }
    return 1;
}

int validation(char** tokens,int count)
{
    if(count!=4)return 0;
    if(strlen(tokens[0])!=1)return 0;
    for(int i =1;i<count;i++)
    {
        if(!is_number(tokens[i]))return 0;
    }
    return 1;
}


void get_table(char* filename)
{
    FILE* fp = fopen(filename,"r");
    if(!fp)
    {
        error = 1;
        return ;
    }
    char line[2000];
    while(fgets(line,sizeof(line),fp))
    {
        char* tokens[100];
        char* symbol = strchr(line,':');
        if(!symbol)
        {
            error =1;
            return;
        }
        int len_before = symbol-line;
        char before_symbol[len_before+1];
        memcpy(before_symbol,line,len_before);
        before_symbol[len_before] = '\0';
        int count = tokenizer(before_symbol,tokens);
        int val = validation(tokens,count);
        if(!val)
        {
            error =1;
            return;
        }

        int len = atoi(tokens[1])*atoi(tokens[2]);
        if(size>=capacity)table_realloc();
        table[size].ch = tokens[0][0];
        table[size].width = atoi(tokens[1]);
        table[size].height = atoi(tokens[2]);
        table[size].depth = atoi(tokens[3]);
        table[size].content = malloc(len+1);
        memcpy(table[size].content,symbol+1,len);
        table[size].content[len] = '\0';
        size++;
    }
}


struct mapping* find_helper(char ch)
{
    for(int i =0;i<size;i++)
    {
        if(ch == table[i].ch)return &table[i];
    }
    return NULL;
}


int max_H()
{
    int res = 1;
    for(int i =0;i<size;i++)
    {
        if((table[i].height-table[i].depth)>res)res = table[i].height - table[i].depth;
    }
    return res;
}

int max_D()
{
    int res = 0;
    for(int i =0;i<size;i++)
    {
        if(table[i].depth>res)res = table[i].depth;
    }
    return res;
}



void print()
{
    char line[2000];
    int first = 1;
    while(fgets(line,sizeof(line),stdin))
    {
        if(!first)putchar('\n');
        first = 0;
        char* n_symbol = strchr(line,'\n');
        *n_symbol = '\0';
        int H = max_H();
        int D = max_D();
        int total_height = H+D;
        for(int l =0;l<total_height;l++)
        {
            // Check if this line has any content
            int has_content = 0;
            char* read = line;
            while(*read)
            {
                struct mapping* map = find_helper(*read);
                struct mapping def_map = {*read,1,1,0,NULL};
                if(!map) map = &def_map;
                int start = H - map->height + map->depth;
                int end = start + map->height -1;

                if(l>=start && l<=end)
                {
                    has_content=1;
                    break;
                }
                read++;
            }

            // If no content, print empty line
            if(!has_content)
            {
                putchar('\n');
                continue;
            }

            // Find the rightmost character with content on this line
            int rightmost = -1;
            read = line;
            int pos = 0;
            while(*read)
            {
                struct mapping* map = find_helper(*read);
                struct mapping def_map = {*read,1,1,0,NULL};
                if(!map) map = &def_map;
                int start = H - map->height + map->depth;
                int end = start + map->height -1;

                if(l>=start && l<=end)
                {
                    rightmost = pos;
                }
                pos++;
                read++;
            }

            // Print the line with content up to rightmost
            read = line;
            pos = 0;
            while(*read)
            {
                struct mapping* map = find_helper(*read);
                struct mapping def_map = {*read,1,1,0,NULL};
                if(!map) map = &def_map;
                int start = H - map->height + map->depth;
                int end = start + map->height -1;

                if(l>=start && l<=end)
                {
                    int row = l - start;
                    if(map->content)
                    {
                        char* row_ptr = map->content + (row*map->width);
                        for(int k=0;k<map->width;k++)
                        {
                            putchar(row_ptr[k]);
                        }
                    }
                    else
                    {
                        putchar(*read);
                    }
                }
                else
                {
                    for(int k=0;k<map->width;k++)
                    {
                        putchar(' ');
                    }
                }

                // Add separator space between characters (except after the last one)
                if(pos < rightmost) putchar(' ');

                if(pos == rightmost) break;
                pos++;
                read++;
            }
            putchar('\n');
        }
    }

}













int main(int argc,char* argv[])
{
    if(argc ==1)
    {
        if(size>=capacity)table_realloc();
        get_table("FONT");
        print();
    }
    else
    {
        if(size>=capacity)table_realloc();
        get_table(argv[1]);
        print();
    }
    cleanup();
    if(error)return 1;
    return 0;
}