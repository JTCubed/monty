#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
	stack_t *stack;
	char *buf, *usage;
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
			{"swap", swap_op},
			{"add", add_op},
			{"nop", nop_op},
			{"div", div_op},
			{"mul", mul_op},
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
				if (strcmp(ops[i].opcode, arglist[0]) == 0)
				{
					opcode_found = 1;
					if (strcmp(ops[i].opcode, "push") == 0)
					{
						if (arglist[1] != NULL && _isdigit(arglist[1]) == 1)
							current_value = atoi(arglist[1]);
						else if (arglist[1][0] == '-')
						{
							if (_isdigit(&arglist[1][1]) == 1)
								current_value = atoi(arglist[1]);
						}
						else
						{
							fprintf(stderr, "L%d: usage: push integer\n", linecount);
							free_tokens(arglist);
							exit(EXIT_FAILURE);
						}
					}
					ops[i].f(&stack, line);
					break;
				}


			}if (!opcode_found)
				 fprintf(stderr, "L%d: unknown instruction %s\n", linecount, arglist[0]);

		linecount++;
		line++;
/*		free(linecpy);
 */		free_tokens(arglist);


	}

	free(buf);
	free_stack(&stack);
	fclose(fp);
	return (0);
}
