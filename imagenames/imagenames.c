#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

static char* def_ext = ".jpg.jpeg.png.tiff.tif";


int is_substring(char* ext,char* symbol)
{
    size_t len = strlen(symbol);
    while(*ext)
    {
        if(strncmp(ext,symbol,len)==0)
        {
            //a problem is .2(symbol) will match .21(ext);
            //so we need also check ext+len
            if(*(ext+len)=='.'||*(ext+len)=='\0')
            return 1;
        }
        ext++;
    }
    return 0;
}

int get_ext(char* res,char* filename)
{
    FILE* fp = fopen(filename,"r");
    if(!fp)
    {
        return 0;
    }
    char line[1000];
    char* write = res;
    while(fgets(line,sizeof(line),fp))
    {
        if(line[0]!='.')
        {
            return 0;
        }
        char* n_symbol = strchr(line,'\n');
        *n_symbol = '\0';
        char* read = line;
        while(*read)
        {
            *write++ = *read++;
        }
    }
    *write = '\0';
    return 1;
}

void read_line(char* filename)
{
    int has_mem = 0;
    char* ext = NULL;
    if(!filename)ext = def_ext;
    else 
    {
        ext =malloc(20000);
        int res= get_ext(ext,filename);
        if(!res)
        {
            free(ext);
            ext = def_ext;
        }
        else has_mem =1;
    }
    char line[1001];
    while(fgets(line,sizeof(line),stdin))
    {
        //delete \n
        char* n_symbol = strchr(line,'\n');
        *n_symbol = '\0';

        //go to final
        char* symbol = line;
        while(*symbol)symbol++;
        symbol--;//now read point to the end of the ext
        while(*symbol!='.')symbol--;//now read point to the final '.'
        

        //check whether its needed ext 
        int res = is_substring(ext,symbol);
        if(res)
        {
            char* itr = symbol;
            //find the start of the name
            while(*itr!='/' && itr !=line)itr--;
            //now itr point to the final '/' or the start
            if(*itr =='/')itr++;
            char buffer[1000];
            size_t len = symbol - itr;
            memcpy(buffer,itr,len);
            buffer[len] = '\0';
            printf("%s\n",buffer);
        }
    }
    if(has_mem)free(ext);
}

int main(int argc,char* argv[])
{
    if(argc ==1)
    {
        read_line(NULL);
        return 1;
    }
    else if(argc ==2)
    {
        read_line(argv[1]);
        return 1;
    }
    else return 0;
}