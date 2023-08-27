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

char *_strcpy(char *dest, char *src)
{
        int len = strlen(src);
        int i;

        for (i = 1; i < len; i++)
        {
                dest[i] = src[i];
        }
        dest[i] = '\0';

        return(dest);
}

char *_strdup(char *str)
{
	int i, j;
	char *s;

	if (str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		;
	s = malloc((sizeof(char) * i) + 1);
	if (s == NULL)
		return (NULL);

	for (j = 0; str[j] != '\0'; j++)
	{
		s[j] = str[j];
	}
	s[j] = '\0';
	return (s);
}
