#include "shell.h"

/**
 * handle_quotes - Gère les guillemets dans une ligne
 * @line_copy: Copie de la ligne à traiter
 * Return: Ligne nettoyée des guillemets
 */
char *handle_quotes(char *line_copy)
{
	int i, j, in_quotes = 0, in_single_quotes = 0;

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

	return (line_copy);
}

/**
 * add_token - Ajoute un token au tableau
 * @tokens: Tableau de tokens
 * @token: Token à ajouter
 * @position: Position actuelle
 * @bufsize: Taille actuelle du buffer
 * @line_copy: Copie de la ligne
 * Return: Nouvelle taille du buffer, ou -1 en cas d'échec
 */
int add_token(char **tokens, char *token, int position, int bufsize,
	char *line_copy)
{
	if (strlen(token) > 0)
	{
		tokens[position] = strdup(token);
		if (!tokens[position])
		{
			int i;

			for (i = 0; i < position; i++)
				free(tokens[i]);
			free(tokens);
			free(line_copy);
			return (-1);
		}
		position++;
	}

	if (position >= bufsize)
	{
		bufsize += 64;
		tokens = realloc(tokens, bufsize * sizeof(char *));
		if (!tokens)
		{
			int i;

			for (i = 0; i < position; i++)
				free(tokens[i]);
			free(line_copy);
			return (-1);
		}
	}

	return (bufsize);
}

/**
 * _split_line - Divise une chaîne en tableau de tokens
 * @line: La chaîne à diviser
 * Return: Tableau de tokens, ou NULL en cas d'échec
 */
char **_split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token, *line_copy;

	if (!tokens)
		return (NULL);

	line_copy = strdup(line);
	if (!line_copy)
	{
		free(tokens);
		return (NULL);
	}

	line_copy = handle_quotes(line_copy);

	token = strtok(line_copy, " \t\r\n");
	while (token != NULL)
	{
		bufsize = add_token(tokens, token, position, bufsize, line_copy);
		if (bufsize == -1)
			return (NULL);
		position++;
		token = strtok(NULL, " \t\r\n");
	}

	tokens[position] = NULL;
	free(line_copy);

	return (tokens);
}

/**
 * free_tokens - Libère la mémoire allouée pour le tableau de tokens
 * @tokens: Tableau de tokens à libérer
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
