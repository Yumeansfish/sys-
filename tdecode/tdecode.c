#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char	*dict[256];

int	check_exist(int idx)
{
	if(dict[idx])return 1;
    return 0;
}

void	get_mapping_table(void)
{
	int		c;
	char	buf[1024];
	char	*write;
	int		in_word;
	int		cur_code;
	int		exist;

	c = getchar();
	// doesnt have mapping table
	if (c < 128)
	{
		ungetc(c, stdin);
		return ;
	}
	// has mapping table
	ungetc(c, stdin);
	write = buf;
	in_word = 0;
	cur_code = 0;
	while ((c = getchar()) != '\n' && c != EOF)
	{
		if (in_word == 0)
		{
			// not in word,give cur_code
			if (c>=128)
			{
				cur_code = c;
				continue ;
			}
			// meet char,start to write
			else if (isalpha((unsigned char)c))
			{
				in_word = 1;
				*write++ = c;
				continue ;
			}
            else if (isspace((unsigned char)c)){
                continue;
            }
            else{
                fprintf(stderr,"invalid");
                exit(EXIT_FAILURE);
            }
		}
		else if (in_word == 1)
		{
			// in word,meet the end
			if (c>=128)
			{
				*write++ = '\0';
				exist = check_exist(cur_code);
				if (exist)
				{
					fprintf(stderr, "invalid");
					exit(EXIT_FAILURE);
				}
				dict[cur_code] = strdup(buf);
				if (!dict[cur_code])
				{
					fprintf(stderr, "mem");
					exit(EXIT_FAILURE);
				}
				write = buf;
				in_word = 0;
				cur_code = c;
				continue ;
			}
			else if (isalpha((unsigned char)c))
			{
				// continue write
				*write++ = c;
				continue ;
			}
            else if (isspace((unsigned char)c)){
                continue;
            }
            else{
                fprintf(stderr,"invalid");
                exit(EXIT_FAILURE);
            }
		}
	}
    // handle orphan
		if (in_word == 1)
		{
            *write = '\0';
			if (check_exist(cur_code))
			{
				fprintf(stderr, "invalid");
				exit(EXIT_FAILURE);
			}
			dict[cur_code] = strdup(buf);
			if (!dict[cur_code])
			{
				fprintf(stderr, "mem");
				exit(EXIT_FAILURE);
			}
		}
}

void	decode_and_print(void)
{
	int	c;

	while ((c = getchar()) != EOF)
	{
		if (c >= 128)
		{
			if (!dict[c])
			{
				fprintf(stderr, "invalid");
				exit(EXIT_FAILURE);
			}
			printf("%s", dict[c]);
		}
		else
		{
			putchar(c);
		}
	}
}

void	cleanup(void)
{
	for (int i = 0; i < 256; i++)
	{
		if (dict[i])
			free(dict[i]);
	}
}

int	main(int argc, char *argv[])
{
	get_mapping_table();
	decode_and_print();
	cleanup();
	return (0);
}
