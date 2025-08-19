#include "shell.h"

/**
 * shell_loop - Main shell loop that handles prompt, reading and validation
 * @program_name: Name of the shell program
 * Return: 0 on success, 1 to continue
 */
int shell_loop(char *program_name)
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
