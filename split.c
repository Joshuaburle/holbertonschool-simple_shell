#include "shell.h"

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
}
