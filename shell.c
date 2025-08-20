#include "shell.h"

/* Affiche l'invite du shell */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
	fflush(stdout);
}

/* Lit une ligne depuis stdin */
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

	/* Supprime le \n de fin de ligne */
	if (read_size > 0 && line[read_size - 1] == '\n')
		line[read_size - 1] = '\0';

	return (line);
}

/* Vérifie si la ligne est vide ou juste des espaces */
int is_empty_or_whitespace(char *line)
{
	int i;

	if (line == NULL)
		return (1);

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ' && line[i] != '\t' &&
			line[i] != '\r' && line[i] != '\n')
			return (0);
	}
	return (1);
}
