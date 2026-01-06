struct lines;
struct lines * lines_create();
void lines_destroy (struct lines * l);
int add_line (struct lines * l, const char * line);
int remove_line (struct lines * l, int id);
int match (struct lines * l, const char * output[], int max_output,
	   const char * words);
