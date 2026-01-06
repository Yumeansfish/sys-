#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

// Exercise 59. (60’) In a source file called alpha.c or alpha.cc write a C or C++ program to encode
// and decode data according to the “alpha” coding scheme defined below. Without command-line
// arguments, the program works in encoding mode, reading data from its standard input and writing
// the corresponding code onto the standard output. Vice-versa, with the -d command-line argument,
// the program works in decoding mode, reading a code from the standard input, and writing the
// corresponding data to the standard output.
// The alpha encoding works as follows. The input is a stream of bytes. The output (or “code”) is a
// stream of the 26 lowercase and 26 uppercase letters of the English language:
// abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ
// As specified later, the code may contain other characters. However, those must be ignored for the
// purpose of decoding. The encoding rules are as follows:
// • An input byte corresponding to a letter other than the letter Q is encoded by an identical out-
// put byte. For example, the sequence of characters “quack” is encoded as the same sequence
// of characters “quack”.
// • The input byte representing the letter Q is encoded by two identical bytes representing the
// letter Q. For example, the input characters “Quote” are encoded as “QQuote”.
// • An input byte b that is not a letter is encoded by the character Q followed by two letters c1c2
// that encode b as follows: c1 and c2 encode numbers between 0 and 15 that are the most
// and least significant four bits of b, respectively. In particular, the values 0, 1, 2, . . . , 15 are
// encoded as a,b, c,. . . ,p, respectively. For example a byte b = 0 is encoded as Qaa; a byte b = 1
// is encoded as Qab; a byte b = 16 is encoded as Qba; a byte b = 33 representing the character
// ‘!’ is encoded as Qcb. Recall that, in general, the most and least significant 4 bits of a byte b
// can be computed (in C/C++) as b / 16 and b % 16, respectively.
// • You may assume the ASCII code. In particular, a letter (a. . . z, A. . . Z) corresponds to a single
// byte, and the numeric codes (byte values) of the letters in alphabetical order are consecutive
// numbers. That is, the code for b is one plus the code for a, and so on.
// In encode mode, the program must output lines of 80 characters. The last line can of course be
// shorter. For example, an input stream consisting of the following four lines:
// Mother, mother
// There’s too many of you crying
// Brother, brother, brother
// There’s far too many of you dying
// Is encoded as the following two lines:
// MotherQcmQcamotherQakThereQchsQcatooQcamanyQcaofQcayouQcacryingQakBrotherQcmQcab
// rotherQcmQcabrotherQakThereQchsQcafarQcatooQcamanyQcaofQcayouQcadyingQak
// When running in decode mode, the program must ignore any non-letter character. So, the program
// must decode the following two lines exactly as the previous ones:
// MotherQcmQcamotherQakThereQchsQcatooQcamanyQcaofQcayouQcacryingQakBrotherQcmQ--
// cabrotherQcmQcabrotherQakThereQchsQcafarQcatooQcamanyQcaofQcayouQcadyingQak!!!!
// With any error, for example with any command-line arguments other than a single -d, or if in
// decode mode the input contains an invalid code, the program must terminate immediately and
// return EXIT_FAILURE. Recall that EXIT_FAILURE is declared in stdlib.h.



void error(char* info)
{
    exit(EXIT_FAILURE);
}

static char* buffer = NULL;



void encode()
{
    int c;
    int count = 0;
    while((c=getchar())!=EOF)
    {
        if(isalpha((unsigned char)c) && c!='Q')
        {
            putchar(c);
            count ++;
            if(count!=0 && count%80 ==0)putchar('\n');
            continue;
        }
        else if(c=='Q')
        {
            putchar('Q');
            count ++;
            if(count!=0 && count%80 ==0)putchar('\n');
            putchar('Q');
            count ++;
            if(count!=0 && count%80 ==0)putchar('\n');
            continue;
        }
        else if(!isalpha((unsigned char)c))
        {
            putchar('Q');
            count ++;
            if(count!=0 && count%80 ==0)putchar('\n');
            unsigned char b = (unsigned char)c;
            unsigned char high = b/16;
            unsigned char low = b % 16;
            putchar(high+'a');
            count ++;
            if(count!=0 && count%80 ==0)putchar('\n');
            putchar(low+'a');
            count ++;
            if(count!=0 && count%80 ==0)putchar('\n');
        }
        else continue;
    }
    if(count!=0)
    putchar('\n');
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


char* skip_non_alpha(char* p)
{
    while(*p && !isalpha((unsigned char)*p))p++;
    return p;
}

void validate_alpha(char ch)
{
    if(ch>='a' && ch<='z')return;
    error("invalid format");
}



void decode()
{
    buffer = malloc(200000);
    convert_to_buffer();
    char* read = buffer;
    while(*read)
    {
        //if not alpha,ignore
        if(!isalpha((unsigned char)*read))
        {
            read++;
            continue;
        }
        //if just one Q,error
        else if(*read =='Q')
        {
            read ++;
            read = skip_non_alpha(read);
            //if after skip no content,error
            if(!*read)
            {
                error("invalid format");
                return;
            }
            //if is 'QQ',put one 'Q' and read++;
            if(*read == 'Q')
            {
                putchar('Q');
                read++;
                continue;
            }
            else 
            {
                char c1 = *read;
                read++;
                read = skip_non_alpha(read);
                //if after skip no content,error
                if(!*read)
                {
                    error("invalid format");
                    return;
                }
                //if is 'Qalphaalpha' decode it and read move;
                char c2 = *read;
                validate_alpha(c1);
                validate_alpha(c2);
                unsigned char high = c1-'a';
                unsigned char low = c2-'a';
                unsigned char origin = 16*high + low;
                putchar(origin);
                read ++;
                continue;
            }
        }
        else
        {
            putchar(*read);
            read++;
            continue;
        }
    }
    free(buffer);
}





int main(int argc,char* argv[])
{
    if(argc == 1)
    {
        encode();
    }
    else
    {
        if(argc !=2)
        {error("command");
            return 0;
        }
        if(strcmp(argv[1],"-d")!=0)
        {
            error("command");
            return 0;
        }
        decode();
    }
}




