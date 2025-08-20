#include "shell.h"

/**
 * resize_tokens - Redimensionne le tableau de tokens
 * @tokens: Tableau actuel
 * @position: Position actuelle
 * @bufsize: Nouvelle taille
 * Return: Nouveau tableau ou NULL si erreur
 */
char **resize_tokens(char **tokens, int position, int bufsize)
{
	char **new_tokens;
	int i;

	new_tokens = realloc(tokens, bufsize * sizeof(char *));
	if (!new_tokens)
	{
		for (i = 0; i < position; i++)
			free(tokens[i]);
		free(tokens);
		return (NULL);
	}
	return (new_tokens);
}

/**
 * _split_line - Divise une ligne en tableau d'arguments
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
			bufsize += 64;
			tokens = resize_tokens(tokens, position, bufsize);
			if (!tokens)
				return (NULL);
		}
		token = strtok(NULL, " \t\r\n");
	}

	tokens[position] = NULL;
	return (tokens);
}

/**
 * free_tokens - Libère la mémoire des tokens
 * @tokens: Tableau de tokens à libérer
 * Return: void
 */
void free_tokens(char **tokens)
{
	int i;

	if (!tokens)
		return;

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);
	free(tokens);
}
