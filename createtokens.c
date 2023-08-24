#include "monty.h"

char **create_tokens(char *str)
{
        char **tokens, *token;
        int max_tokens, count;
        const char *delim;

        max_tokens = strlen(str);
        tokens = malloc(sizeof(char *) * (max_tokens + 1));
        delim = " \t\n";
        count = 0;

        if (tokens == NULL)
                exit(-1);

        token = strtok(str, delim);

        while (token != NULL)
        {
                tokens[count] = malloc(strlen(token) + 1);
		if (tokens[count] == NULL)
			exit(-1);
		strcpy(tokens[count], token);

                count++;
                token = strtok(NULL, delim);
        }
        tokens[count] = NULL;

        return (tokens);
}
