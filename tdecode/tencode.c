

static char			buffer[100000];

struct				word_info
{
	char			*word;
	int				feq;
    int             len;
    int             gain;
    int             code;
};

struct word_info		*word_info_table = NULL;
int					word_info_table_capacity = 0;
int 				word_info_count = 0;

void	error(char *content)
{
	fprintf(stderr, content);
	exit(EXIT_FAILURE);
}

int calculate_gain_helper(struct word_info* info){
    return (info->feq * info->len) - (info->feq * 1) - (info->len+1);
}


void calculate_gain(){
    for(int i=0;i<word_info_table_count;i++){
        word_info_table[i] .gain = calculate_gain_helper(&word_info_table[i]);
    }
}


int compare_word_info(const void *a,const void *b){
    struct word_info *wa = (struct word_info *) a;
    struct word_info *wb = (struct word_info *) b;
    //compare gain
    if(wa->gain != wb->gain){
        return wb->gain - wa->gain;
    }
    return strcmp(wa->word,wb->word);

}



void	word_info_table_realloc()
{
	//first initial,give 10
	if(word_info_table_capacity == 0){
		void *tmp = realloc(word_info_table,sizeof(struct word_info)*10);
		if(!tmp)error("mem");
		word_info_table = tmp;
		word_info_table_capacity = 10;
	}
	else
	{
		void *tmp = realloc(word_info_table,(word_info_table_capacity*2)*sizeof(struct word_info));
		if (!tmp)error("mem");
		word_info_table = tmp;
		word_info_table_capacity*=2;
	}
}

void	add_word_info(char *word,int len)
{
	if(word_info_table_count ==  word_info_table_capacity){
		word_info_table_realloc();
	}
	word_info_table[word_info_table_count].word = strdup(word);
    if(!word_info_table[word_info_table_count].word){
        error("mem");
    }
    word_info_table[word_info_table_count].len = len;
    word_info_table[word_info_table_count].feq = 1;
	word_info_table[word_info_table_count].code = 0;
	word_info_count ++;
}


struct word_info * find(char* word){
    for(int i = 0;i<word_info_table_count;i++){
        if(strcmp(word_info_table[i].word,word)==0){
            return &word_info_table[i];
        }
    }
    return NULL;
}

void	collect_word_info_table(void)
{
	char			word[1000];
	char			*read;
	char			*write;
	int				in_word;
	struct word_info	*target;
	int 			len;


	read = buffer;
	write = word;
	in_word = 0;
	while (*read)
	{
		if (in_word == 0)
		{
			if (isalpha(*read))
			{
				// write it in word and move ptr
				in_word = 1;
				*write++ = *read++;
			}
			else
			{
				// still no word,only move read
				read++;
			}
		}
		else if (in_word == 1)
		{
			// write it in word and move ptr
			if (isalpha(*read))
			{
				*write++ = *read++;
			}
			// end this word
			else
			{
				in_word = 0;
                *write = '\0';
				target = find(word);
				if (!target)
				{
                    len = write - word;
					add_word_info(word,len);
                    write = word;
				}
				else if (target)
				{
					target->feq++;
                    write = word;
				}
			}
		}
	}
	// handle orphan
	if (in_word == 1)
	{
		*write = '\0';
		len = write - word;
		target = find(word);
		if (!target)
			add_word_info(word, len);
		else if (target)
		{
			target->feq++;
		}
	}
}

void	write_to_buffer(void)
{
	int		c;
	char	*write;

	write = buffer;
	while ((c = getchar()) != EOF)
	{
		*write++ = c;
	}
    *write = '\0';
}

void calculate_code(){
	int count = 0;
    for(int i =0;i<word_info_table_count;i++){
        if(word_info_table[i].gain >0 && count < 128){
        word_info_table[i].code = 128+count;
		count ++;
        }
    }
}


void cleanup(){
    for(int i =0;i<word_info_table_count;i++){
        if(word_info_table[i].word){
        free(word_info_table[i].word);
        }
    }
	free(word_info_table);
}

void encode(){
	for(int i =0;i<128;i++){
		if(i<word_info_table_count &&word_info_table[i].code >= 128){
			printf("%s\n",word_info_table[i].word);
		}
		else{
			printf("\n");
		}
	}
}

void print(){
	char * read = buffer;
	int in_word = 0;
	char word[1000];
	char* write;
	while(*read)
	{
		if(in_word == 0){
			if(!isalpha(*read)){
				putchar(*read);
				read++;
			}
			else if(isalpha(*read)){
				in_word = 1;
				write = word;
				*write ++ = *read++;
			}
		}
		else if (in_word==1){
			//end , firstly find it in table
			if(!isalpha(*read)){
				in_word = 0;
				*write = '\0';
				struct word_info* target = find(word);
				if(target&&target->code){
					putchar(target->code);	
					write = word;		
				}
				else{
					printf("%s",word);
					write = word;
				}
				putchar(*read);
				read++;
			}
			else if(isalpha(*read)){
				*write ++ = *read++;
			}
		}
	}
	//handle orphan
	if(in_word == 1){
		*write = '\0';
		struct word_info* target = find(word);
		if(target && target->code){
			putchar(target->code);
			write= word;
		}
		else{
			printf("%s",word);
		}
		
	}
}

int	main(int argc, char *argv[])
{
	write_to_buffer();
	collect_word_info_table();
    calculate_gain();
    qsort(word_info_table,word_info_table_count,sizeof(struct word_info),compare_word_info);
    calculate_code();
    encode();
	print();
    cleanup();
}