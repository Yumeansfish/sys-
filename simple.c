#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constants

#define MAX_LABEL_NAME_LENGTH 50
#define MAX_LINE_LENGTH 1024
#define DELIM " \t"

// enum
typedef enum
{
	INS_ASSIGN,
	INS_OUTPUT,
	INS_HALT,
	INS_IF,
	INS_GOTO,
	INS_INPUT
}							InstructionType;

typedef enum
{
	OP_NONE,
	OP_ADD,
	OP_SUB,
	OP_DIV,
	OP_MUL,
	OP_EQ,
	OP_NE,
	OP_LT,
	OP_GT,
	OP_LE,
	OP_GE
}							OpType;

// data structure
struct						operand
{
	char					reg;
	int						immediate;
	// memory flags: 0 = register/immediate, 1 = memory
	int						is_mem;
};

struct						instruction
{
	InstructionType			type;
	struct operand dest;   // destination can be reg/mem
	struct operand first;  // left can from reg/mem/immediate
	struct operand second; // right can from reg/mem/immediate
	OpType					op;
	int						target_addr;
};

// mapping table
static const struct
{
	const char *str;
	OpType type;
} op_table[] = {{"+", OP_ADD},
				{"-", OP_SUB},
				{"*", OP_MUL},
				{"/", OP_DIV},
				{"==", OP_EQ},
				{"!=", OP_NE},
				{"<", OP_LT},
				{">", OP_GT},
				{"<=", OP_LE},
				{">=", OP_GE},
				// sentinel
				{NULL, 0}};

struct						label
{
	char					name[MAX_LABEL_NAME_LENGTH];
	int						instruction_idx;
};

// global vars
static int					reg[26] = {0};
static int					pc = 0;

// dynamic memory
static int					*memory = NULL;
static int					memory_capacity = 0;

// dynamic programs
static struct instruction	*program = NULL;
static int					program_capacity = 0;

// dynamic labels
static struct label			*label_table = NULL;
static int					label_capacity = 0;

// counter
int							label_count = 0;
int							program_size = 0;

// tokenizer buf
static char					tokenize_buf[MAX_LINE_LENGTH];

// error handling
void	error(const char *error)
{
	fprintf(stderr, "%s\n", error);
	exit(1);
}

void	program_realloc(int idx)
{
	int					new_capacity;
	struct instruction	*new_program;

	new_capacity = idx + 1;
	new_program = realloc(program, new_capacity * sizeof(struct instruction));
	if (!new_program)
		error("fail in realloc program");
	// reset all fields of new programs to zero
	for (int i = program_capacity; i < new_capacity; i++)
	{
		memset(&new_program[i], 0, sizeof(struct instruction));
	}
	program = new_program;
	program_capacity = new_capacity;
}

void	label_realloc(int idx)
{
	int				new_capacity;
	struct label	*new_label;

	new_capacity = idx + 1;
	new_label = realloc(label_table, new_capacity * sizeof(struct label));
	if (!new_label)
		error("fail in realloc label");
	label_table = new_label;
	label_capacity = new_capacity;
}

// formatter
// trimmer for every line
void	trimmer(char *line)
{
	char	*comment;
	char	*start;
	int		len;

	// find comments sign and trancate
	comment = strchr(line, '#');
	if (comment)
	{
		*comment = '\0'; //
	}
	// delete the front space
	start = line;
	while (*start && isspace(*start))
	{
		start++;
	}
	// if the start moved,means have front space,then move real start the line
	if (start != line)
	{
		memmove(line, start, strlen(start) + 1);
	}
	// delete the back space
	len = strlen(line);
	while (len > 0 && isspace(line[len - 1]))
	{
		line[--len] = '\0';
	}
}

// validator
// validate whether its valid reg form
void	validator_reg(char reg)
{
	if (reg < 'a' || reg > 'z')
		error("invalid reg char");
}

// validator whether its valid number
void	validator_integer(const char *str)
{
	// skip the sign
	if (*str == '+' || *str == '-')
		str++;
	// doesnot have number
	if (*str == '\0')
		error("invalid number");
	// check whether only digit
	while (*str)
	{
		if (!isdigit(*str))
			error("invalid number");
		str++;
	}
}

// check whether its label line
int	is_label_line(char *line)
{
	int	len;

	len = strlen(line);
	if (len < 2)
		return (0);
	if (line[len - 1] != ':')
		return (0);
	for (int i = 0; i < len - 1; i++)
	{
		if (isspace(line[i]))
			return (0);
	}
	return (1);
}

void	add_label(char *line, int instruction_idx)
{
	int	len;

	len = strlen(line);
	// check whether the name length satisfied(delete:)
	if (len > MAX_LABEL_NAME_LENGTH + 1)
		error("so long label");
	// check whether counts of label satisfied
	if (label_count >= label_capacity)
		label_realloc(label_count);
	// copy without :
	memcpy(label_table[label_count].name, line, len - 1);
	label_table[label_count].name[len - 1] = '\0';
	label_table[label_count].instruction_idx = instruction_idx;
	label_count++;
}

void	collect_label(const char *filename)
{
	FILE	*fp;
	char	line[MAX_LINE_LENGTH];
	int		instruction_idx;
	int		ins_line;

	// set initial to 1 first
	ins_line = 1;
	fp = fopen(filename, "r");
	// check whether open successfully
	if (!fp)
	{
		perror("fopen");
		exit(1);
	}
	instruction_idx = 0;
	while (fgets(line, sizeof(line), fp))
	{
		// trim first
		trimmer(line);
		// then if after trim is '\0',skip
		if (line[0] == '\0')
			continue ;
		// record label if contains label
		// we add it in label table at first
		// then in parser phase we add label in
		// table on the ins->next_addr
		if (is_label_line(line) && ins_line == 0)
			error("after label is still label");
		else if (is_label_line(line) && ins_line == 1)
		{
			add_label(line, instruction_idx);
			ins_line = 0;
		}
		else
		{
			ins_line = 1;
			instruction_idx++;
		}
	}
	// check whether the orphan one is still label(cannot end with label)
	if (ins_line == 0)
		error("after label is still label");
	fclose(fp);
}

InstructionType	get_instruction_type(char *line)
{
	char	buf[MAX_LINE_LENGTH];
	char	*token;

	strcpy(buf, line);
	token = strtok(buf, DELIM);
	if (token == NULL)
		error("invalid instruction");
	// use first token to differentiate type
	if (strcmp(token, "halt") == 0)
		return (INS_HALT);
	if (strcmp(token, "goto") == 0)
		return (INS_GOTO);
	if (strcmp(token, "if") == 0)
		return (INS_IF);
	if (strcmp(token, "input") == 0)
		return (INS_INPUT);
	if (strcmp(token, "output") == 0)
		return (INS_OUTPUT);
	return (INS_ASSIGN);
}

int	find_label(char *label)
{
	for (int i = 0; i < label_count; i++)
	{
		if (strcmp(label_table[i].name, label) == 0)
		{
			return (label_table[i].instruction_idx);
		}
	}
	fprintf(stderr, "cannot find label");
	exit(1);
}

// tokenizer
// this function is responsible for:
// 1.copy the line into tokenize_buf
// 2.divie tokens
// 3.return the tokens amounts
int	tokenizer(char *line, char **tokens, int max_tokens)
{
	char	*token;
	int		count;

	strcpy(tokenize_buf, line);
	count = 0;
	token = strtok(tokenize_buf, DELIM);
	while (token != NULL && count < max_tokens)
	{
		tokens[count++] = token;
		token = strtok(NULL, DELIM);
	}
	if (token != NULL)
		error("token so much");
	return (count);
}

//validate whether actual tokens=needed_tokens
void tokenizer_validate_version(char*line,char **tokens,int needed_tokens){
	int count = tokenizer(line,tokens,needed_tokens);
	if(count != needed_tokens)
	error("invalid token amunts");
}

// helper function for parse operand
// some are allowed to use immediate(for example,output)
// check the form is mem/reg at first if not both then check whether its
// valid immediate
void	parse_operand(char *token, struct operand *oper, int allow_immediate)
{
	// if its mem
	if (token[0] == '@')
	{
		// check whether length of @c
		if (strlen(token) != 2)
			error("invalid token");
		oper->is_mem = 1;
		// validating before change reg
		validator_reg(token[1]);
		oper->reg = token[1];
	}
	// if its reg
	else if (strlen(token) == 1 && token[0] >= 'a' && token[0] <= 'z')
	{
		oper->is_mem = 0;
		validator_reg(token[0]);
		oper->reg = token[0];
	}
	// immediate
	else
	{
		if (!allow_immediate)
			error("invalid operand");
		oper->is_mem = 0;
		oper->reg = 0;
		validator_integer(token);
		oper->immediate = atoi(token);
	}
}

void	parse_goto(char *line, struct instruction *ins)
{
	char	*tokens[2];

	tokenizer_validate_version(line, tokens, 2);
	// format:
	// token[0]:goto
	// token[1]:label
	ins->type = INS_GOTO;
	ins->target_addr = find_label(tokens[1]);
}

void	parse_if(char *line, struct instruction *ins)
{
	char	*tokens[3];

	tokenizer_validate_version(line, tokens, 3);
	// format:
	// token[0] = if
	// token[1] = first oper
	// token[2] = label
	ins->type = INS_IF;
	ins->target_addr = find_label(tokens[2]);
	// if only has first oper and doesnt have immediate
	parse_operand(tokens[1], &ins->first, 0);
}

void	parse_input(char *line, struct instruction *ins)
{
	char	*tokens[3];

	tokenizer_validate_version(line, tokens, 3);
	// format:
	// token[0] = input
	// token[1] = dest oper
	// token[2] = first oper
	ins->type = INS_INPUT;
	// input has dest and first and no immediate
	parse_operand(tokens[1], &ins->dest, 0);
	parse_operand(tokens[2], &ins->first, 0);
}

void	parse_output(char *line, struct instruction *ins)
{
	char	*tokens[2];

	tokenizer_validate_version(line, tokens, 2);
	ins->type = INS_OUTPUT;
	// format:
	// token[0] = output
	// token[1] = first oper
	// output use first oper and can use immediate
	parse_operand(tokens[1], &ins->first, 1);
}

OpType	get_op_type(char *op_str)
{
	for (int i = 0; op_table[i].str != NULL; i++)
	{
		if (strcmp(op_str, op_table[i].str) == 0)
			return (op_table[i].type);
	}
	fprintf(stderr, "invalid op");
	exit(1);
}

void	parse_assign(char *line, struct instruction *ins)
{
	char	*tokens[5];
	int		count;

	// use tokenizer to differient whether it has op
	count = tokenizer(line, tokens, 5);
	if (count == 3)
	{
		if (strcmp(tokens[1], "=") != 0)
			error("invalid instruction");
		ins->type = INS_ASSIGN;
		ins->op = OP_NONE;
		// format
		// token[0] = dest oper
		// token[1] = "="
		// token[2] = first oper
		parse_operand(tokens[0], &ins->dest, 0);
		parse_operand(tokens[2], &ins->first, 1);
	}
	else if (count == 5)
	{
		if (strcmp(tokens[1], "=") != 0)
			error("invalid instruction");
		ins->type = INS_ASSIGN;
		ins->op = get_op_type(tokens[3]);
		// format
		// token[0]:dest oper
		// token[1]:= "=""
		// token[2]:first oper
		// token[3]:op
		// token[4]:second oper
		parse_operand(tokens[0], &ins->dest, 0);
		parse_operand(tokens[2], &ins->first, 1);
		parse_operand(tokens[4], &ins->second, 1);
	}
	else
	{
		error("invalid instruction");
	}
}

void	parse_instruction(char *line, struct instruction *ins)
{
	InstructionType	cur_type;

	cur_type = get_instruction_type(line);
	switch (cur_type)
	{
	// HALT dont need more field
	case INS_HALT:
		ins->type = cur_type;
		break ;
	// GOTO need type and target_addr
	case INS_GOTO:
		parse_goto(line, ins);
		break ;
	// IF need type and target_addr and src1
	case INS_IF:
		parse_if(line, ins);
		break ;
		// input need type and src1 and dest
	case INS_INPUT:
		parse_input(line, ins);
		break ;
	case INS_OUTPUT:
		// output need type  + immediate / src
		parse_output(line, ins);
		break ;
	case INS_ASSIGN:
		// assign need type + at least one(immediate/src)
		parse_assign(line, ins);
		break ;
	}
}

void	parser(const char *filename)
{
	FILE	*fp;
	int		pc;
	char	line[MAX_LINE_LENGTH];

	fp = fopen(filename, "r");
	if (!fp)
	{
		perror("fopen");
		exit(1);
	}
	pc = 0;
	while (fgets(line, sizeof(line), fp))
	{
		// trim at first
		trimmer(line);
		// then if trim to '\0',skip
		if (line[0] == '\0')
			continue ;
		// skip the label line
		if (is_label_line(line))
			continue ;
		if (pc >= program_capacity)
			program_realloc(pc);
		// construct a sequenced instruction table
		parse_instruction(line, &program[pc]);
		pc++;
	}
	program_size = pc;
	fclose(fp);
}

void	load_program(const char *filename)
{
	// collect label first
	collect_label(filename);
	// parsing in c
	parser(filename);
}

void	mem_realloc(int addr)
{
	int	new_capacity;
	int	*new_memory;

	new_capacity = addr + 1;
	new_memory = realloc(memory, new_capacity * sizeof(int));
	if (!new_memory)
		error("fail in realloc mem");
	// initialize
	for (int i = memory_capacity; i < new_capacity; i++)
	{
		new_memory[i] = 0;
	}
	memory = new_memory;
	memory_capacity = new_capacity;
}

// execute part
int	get_value(struct operand *oper)
{
	int	addr;

	// check whether reg exist first
	if (oper->reg != 0)
	{
		// mem
		if (oper->is_mem)
		{
			addr = reg[oper->reg - 'a'];
			if (addr < 0)
				error("invalid mem address");
			// extend mem
			if (addr >= memory_capacity)
				mem_realloc(addr);
			return (memory[addr]);
		}
		// reg
		return (reg[oper->reg - 'a']);
	}
	// immediate
	return (oper->immediate);
}

void	write_value(struct operand *oper, int value)
{
	int	addr;

	if (oper->is_mem)
	{
		addr = reg[oper->reg - 'a'];
		if (addr < 0)
			error("invalid mem address");
		if (addr >= memory_capacity)
			mem_realloc(addr);
		memory[addr] = value;
	}
	else
	{
		reg[oper->reg - 'a'] = value;
	}
}

void	execute_assign(struct instruction *ins)
{
	int	v1;
	int	v2;
	int	res;

	// handle the execution
	v1 = get_value(&ins->first);
	v2 = get_value(&ins->second);
	switch (ins->op)
	{
	case OP_ADD:
		res = v1 + v2;
		break ;
	case OP_SUB:
		res = v1 - v2;
		break ;
	case OP_DIV:
		if (v2 == 0)
			error("division zero");
		res = v1 / v2;
		break ;
	case OP_MUL:
		res = v1 * v2;
		break ;
	case OP_NONE:
		res = v1;
		break ;
	case OP_EQ:
		res = v1 == v2;
		break ;
	case OP_LT:
		res = v1 < v2;
		break ;
	case OP_GT:
		res = v1 > v2;
		break ;
	case OP_GE:
		res = v1 >= v2;
		break ;
	case OP_LE:
		res = v1 <= v2;
		break ;
	case OP_NE:
		res = v1 != v2;
		break ;
	default:
		error("invalid op");
	}
	// write back to destination register or memory
	write_value(&ins->dest, res);
}

void	execute_output(struct instruction *ins)
{
	int	v;
	int	n;

	v = get_value(&ins->first);
	n = printf("%d\n", v);
	if (n < 0)
		error("invalid output");
}

// dest store the input value
// first store the eof flag
void	execute_input(struct instruction *ins)
{
	int	value;
	int	r;

	// check whether scanf sucessful
	r = scanf("%d", &value);
	if (r == 1)
	{
		write_value(&ins->dest, value);
		write_value(&ins->first, 0);
	}
	else
	{
		write_value(&ins->first, 1);
	}
}

void	execute_program(void)
{
	struct instruction	*ins;

	while (1)
	{
		// check whether pc whether over bound
		if (pc >= program_size)
			return ;
		// get the ins that pc point to
		ins = &program[pc];
		switch (ins->type)
		{
		case INS_ASSIGN:
			execute_assign(ins);
			pc++;
			break ;
		case INS_OUTPUT:
			execute_output(ins);
			pc++;
			break ;
		case INS_INPUT:
			execute_input(ins);
			pc++;
			break ;
		case INS_HALT:
			return ;
		case INS_GOTO:
			pc = ins->target_addr;
			break ;
		case INS_IF:
			if (get_value(&ins->first) != 0)
				pc = ins->target_addr;
			else
				pc++;
			break ;
		}
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		error("invalid file");
	}
	load_program(argv[1]);
	execute_program();
	return (0);
}
