#include "shell.h"

/**
 * _split_line - Splits a string into an array of tokens
 * @line: The string to split
 * Return: Array of tokens, or NULL on failure
 */
char **_split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token, *line_copy;
	int i, j, in_quotes = 0, in_single_quotes = 0;

	if (!tokens)
		return (NULL);

	/* Make a copy to avoid modifying original line */
	line_copy = strdup(line);
	if (!line_copy)
	{
		free(tokens);
		return (NULL);
	}

	/* Remove quotes and handle spaces properly */
	for (i = 0, j = 0; line_copy[i] != '\0'; i++)
	{
		if (line_copy[i] == '"' && !in_single_quotes)
		{
			in_quotes = !in_quotes;
			continue;
		}
		if (line_copy[i] == '\'' && !in_quotes)
		{
			in_single_quotes = !in_single_quotes;
			continue;
		}
		if (!in_quotes && !in_single_quotes && 
			(line_copy[i] == ' ' || line_copy[i] == '\t'))
		{
			line_copy[j++] = ' ';
		}
		else
		{
			line_copy[j++] = line_copy[i];
		}
	}
	line_copy[j] = '\0';

	/* Split the cleaned line */
	token = strtok(line_copy, " \t\r\n");
	while (token != NULL)
	{
		/* Skip empty tokens */
		if (strlen(token) > 0)
		{
			tokens[position] = strdup(token);
			if (!tokens[position])
			{
				/* Cleanup on error */
				for (i = 0; i < position; i++)
					free(tokens[i]);
				free(tokens);
				free(line_copy);
				return (NULL);
			}
			position++;
		}

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				/* Cleanup on error */
				for (i = 0; i < position; i++)
					free(tokens[i]);
				free(line_copy);
				return (NULL);
			}
		}

		token = strtok(NULL, " \t\r\n");
	}

	tokens[position] = NULL;
	free(line_copy);
	return (tokens);
}

/**
 * free_tokens - Frees memory allocated for tokens array
 * @tokens: Array of tokens to free
 */
void free_tokens(char **tokens)
{
	int i;

	if (tokens)
	{
		for (i = 0; tokens[i] != NULL; i++)
			free(tokens[i]);
		free(tokens);
	}
}
