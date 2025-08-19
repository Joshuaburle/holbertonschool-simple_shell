#include "shell.h"

/**
 * display_prompt - Affiche le prompt du shell
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
	fflush(stdout);
}

/**
 * read_line - Lit une ligne depuis l'entrée standard
 * Return: Pointeur vers la ligne, ou NULL en cas de fin de fichier
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_size;

	read_size = getline(&line, &len, stdin);
	if (read_size == -1)
	{
		free(line);
		return (NULL);
	}

	/* Suppression du caractère de nouvelle ligne */
	if (read_size > 0 && line[read_size - 1] == '\n')
		line[read_size - 1] = '\0';

	return (line);
}

/**
 * is_empty_or_whitespace - Vérifie si la ligne est vide ou ne contient 
 * que des espaces
 * @line: La ligne à vérifier
 * Return: 1 si vide/espaces, 0 sinon
 */
int is_empty_or_whitespace(char *line)
{
	int i;

	if (line == NULL)
		return (1);

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r' && line[i] != '\n')
			return (0);
	}
	return (1);
}
