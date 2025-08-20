#include "shell.h"

<<<<<<< HEAD
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
=======
/**
 * split - Divise une ligne en un seul argument (pour la tâche 0.1)
 * @line: La ligne à analyser
 * Return: Tableau avec un seul argument, ou NULL en cas d'erreur
 */
char **split(char *line)
{
	char **args = malloc(2 * sizeof(char *));
	char *token;

	if (args == NULL)
		return (NULL);

	/* Prendre seulement le premier mot (pas d'arguments) */
	token = strtok(line, " \t\r\n");
	if (token == NULL)
	{
		free(args);
		return (NULL);
	}

	args[0] = token;
	args[1] = NULL;

	return (args);
>>>>>>> 611fa6806319d37f6a3870695839823de17f4a11
}
