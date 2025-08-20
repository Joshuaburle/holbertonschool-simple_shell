#include "shell.h"

/**
 * _split_line - Divise une chaîne en tableau de tokens
 * @line: La chaîne à diviser
 * Return: Tableau de tokens, ou NULL en cas d'échec
 */
char **_split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
		return (NULL);

	/* Divise par espaces, tabs et retours à la ligne */
	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		tokens[position] = strdup(token);
		if (!tokens[position])
		{
			int i;

			/* Libère la mémoire en cas d'erreur */
			for (i = 0; i < position; i++)
				free(tokens[i]);
			free(tokens);
			return (NULL);
		}
		position++;

		/* Agrandit le tableau si nécessaire */
		if (position >= bufsize)
		{
			char **new_tokens;

			bufsize += 64;
			new_tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!new_tokens)
			{
				int i;

				for (i = 0; i < position; i++)
					free(tokens[i]);
				free(tokens);
				return (NULL);
			}
			tokens = new_tokens;
		}
		token = strtok(NULL, " \t\r\n");
	}

	tokens[position] = NULL;
	return (tokens);
}

/* Libère la mémoire des tokens */
void free_tokens(char **tokens)
{
	int i;

	if (!tokens)
		return;

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);
	free(tokens);
}
