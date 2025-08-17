#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * _split_line - Split a line into tokens
 * @line: The line to split
 * Return: Array of tokens
 */
char **_split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;
	char *line_copy = strdup(line);

    if (!tokens)
    {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n");
    }

    tokens[position] = NULL;
    return tokens;
}
