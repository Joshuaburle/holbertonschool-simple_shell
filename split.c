#include "shell.h"

char **_split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token;

	if (!tokens)
		return NULL;

	token = strtok(line, " \t");
	while (token != NULL)
	{
		tokens[position] = strdup(token);
		if (!tokens[position])
		{
			int i;
			for (i = 0; i < position; i++)
				free(tokens[i]);
			free(tokens);
			return NULL;
		}
		position++;

		if (position >= bufsize)
		{
			char **new_tokens;
			bufsize += 64;
			new_tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (!new_tokens)
			{
				int i;
				for (i = 0; i < position; i++)
					free(tokens[i]);
				free(tokens);
				return NULL;
			}
			tokens = new_tokens;
		}
		token = strtok(NULL, " \t");
	}
	tokens[position] = NULL;
	return tokens;
}

void free_tokens(char **tokens)
{
	int i;

	if (!tokens)
		return;

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);
	free(tokens);
}
