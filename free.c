#include "monty.h"

void free_tokens(char **tokens)
{
    int i = 0;
    while(tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}


void free_stack(stack_t **stack)
{
	stack_t *temp;

	while (*stack)
	{
		temp = *stack;
		*stack = (*stack)->next;
		free(temp);
	}
}
