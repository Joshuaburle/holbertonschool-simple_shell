#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
	fflush(stdout);
}

/**
 * read_line - Reads a line from stdin
 * Return: Pointer to the line, or NULL on EOF
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

	/* Remove newline character */
	if (read_size > 0 && line[read_size - 1] == '\n')
		line[read_size - 1] = '\0';

	return (line);
}

/**
 * is_empty_or_whitespace - Checks if line is empty or only whitespace
 * @line: The line to check
 * Return: 1 if empty/whitespace, 0 otherwise
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
