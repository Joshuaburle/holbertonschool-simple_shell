#include "shell.h"

/* Affiche le prompt en mode interactif */
void display_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/* Lit une ligne sur stdin, remplace '\n' par '\0' */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread = getline(&line, &len, stdin);

	if (nread == -1)
	{
		free(line);
		return NULL;
	}
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';
	return line;
}

/* 1 si vide/espaces, 0 sinon */
int is_empty_or_whitespace(char *line)
{
	int i;

	if (!line)
		return 1;
	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ' && line[i] != '\t' &&
			line[i] != '\r' && line[i] != '\n')
			return 0;
	}
	return 1;
}
