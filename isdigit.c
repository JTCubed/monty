#include "monty.h"
#include <ctype.h>

/**
 * _isdigit - check the code
 *
 *@c : ASCII equivalent
 *
 * Return: 1 if c  is a letter, lowercase or uppercase
 *
 */


int _isdigit(char *str)
{
	if (!str || *str == '\0')
		return (0);

	if (*str == '\0')
		return (0);

	while (*str)
	{
		if (!isdigit((unsigned char)*str))
			return (0);
		str++;
	}

	return (1);
}
