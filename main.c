#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
	stack_t *stack;
	char *usage;
	char *buf;
	FILE *fp;
	size_t len;
	ssize_t read;
	char *linecpy;
	char **arglist;
	int i, linecount, opcode_found;
	unsigned int line;
	instruction_t ops[] =
		{
			{"push", (void (*)(stack_t **, unsigned int))push_op},
			{"pall", pall_op},
			{"pint", pint_op},
			{"pop", pop_op},
			{NULL, NULL}
		};


	usage = "USAGE: monty file\n";
	buf = NULL;
	opcode_found = 0;
	stack = NULL;
	len = 0;


	if (argc != 2)
	{
		write(STDERR_FILENO, usage, strlen(usage));
		exit(EXIT_FAILURE);
	}

	fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	linecount = 1;
	line = 1;
	while ((read = getline(&buf, &len, fp)) != -1)
	{

 		linecpy = buf;
		arglist = create_tokens(linecpy);
		if (arglist[0] != NULL)
			for (i = 0; ops[i].opcode; i++)
			{
				if (strcmp(ops[i].opcode, "push") == 0 && arglist[1] != NULL)
				{
					if (_isdigit(arglist[1]) == 1)
					{
						current_value = atoi(arglist[1]);
						ops[i].f(&stack, read);
						opcode_found = 1;
						break;
					}else
					{
						fprintf(stderr, "L%d: usage: push integer\n", linecount);
						exit(EXIT_FAILURE);
					}
				}
				else if (strcmp(ops[i].opcode, "pall") == 0)
				{
					ops[i].f(&stack, read);
					opcode_found = 1;
					break;
				}
				else if (strcmp(ops[i].opcode, "pint") == 0)
				{
					ops[i].f(&stack, line);
					opcode_found = 1;
					break;
				}
				else if (strcmp(ops[i].opcode, "pop") == 0)
				{
					ops[i].f(&stack, line);
					opcode_found = 1;
					break;
				}
			}if (!opcode_found)
				 fprintf(stderr, "L%d: unknown instruction %s\n", linecount, arglist[0]);

		linecount++;
		line++;
 	}

	fclose(fp);
	return (0);
}
