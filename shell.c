#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
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

	if (line == NULL || strlen(line) == 0)
		return (1);

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
	}
	return (1);
}
int shell_loop(char *program_name)
>>>>>>> 12312beb0aefd0a490e3e6ff39a797583c1395ec
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_size;
	int i, is_empty;

	/* Display prompt in interactive mode */
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		fflush(stdout);
	}

	/* Read line from stdin */
	read_size = getline(&line, &len, stdin);
	if (read_size == -1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		return (0); /* Exit */
	}

	/* Remove newline character */
	if (read_size > 0 && line[read_size - 1] == '\n')
		line[read_size - 1] = '\0';

	/* Check if line is empty or only whitespace */
	if (line == NULL || strlen(line) == 0)
	{
		free(line);
		return (1); /* Continue */
	}

	is_empty = 1;
	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			is_empty = 0;
			break;
		}
	}

	if (is_empty)
	{
		free(line);
		return (1); /* Continue */
	}

	/* Execute command */
	return (execute_command(line, program_name));
}
