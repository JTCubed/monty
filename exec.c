#include "monty.h"

int current_value = 0;

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

void pint_op(stack_t **stack, unsigned int line_number)
{
	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

void pop_op(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = (*stack)->next;
	if (*stack)
		(*stack)->prev = NULL;
	free(temp);
}

void swap_op(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (!(*stack) || !((*stack)->next))
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}

void add_op(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	int result;

	if (!(*stack) || !((*stack)->next))
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	result = (*stack)->n + (*stack)->next->n;

	(*stack)->next->n = result;

	temp = *stack;

	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}

void nop_op(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

void div_op(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (!(*stack) || !((*stack)->next))
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n /= (*stack)->n;
	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}

void mul_op(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (!(*stack) || !((*stack)->next))
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n *= (*stack)->n;
	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(temp);
}
