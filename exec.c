#include "monty.h"

void push_op(stack_t **stack, unsigned int line_number)
{
	stack_t *new;
	(void)line_number;

	new = malloc(sizeof(stack_t));
	if (!new)
	{
		fprintf(stderr, "Error: Malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new->n = current_value;
	new->prev = NULL;
	new->next = *stack;

	if (*stack)
	{
		(*stack)->prev = new;
	}
	*stack = new;
}

void pall_op(stack_t **stack, unsigned int line_number)
{
	stack_t *current;
	(void)line_number;

	current = *stack;
	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/*instruction_t ops[] =
{
	{"push", (void (*)(stack_t **, unsigned int))push_op},
	{"pall", pall_op},
	{NULL, NULL}
};
*/
