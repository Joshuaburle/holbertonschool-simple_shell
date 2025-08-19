#include "shell.h"

/**
 * main - Entry point of the shell
 * @argc: Number of arguments
 * @argv: Array of arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line;
	int status = 1;

	(void)argc;

	while (status)
	{
		/* Display prompt in interactive mode */
		if (isatty(STDIN_FILENO))
			display_prompt();

		/* Read command line */
		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Execute command */
		status = execute_command(line, argv[0]);

		/* Clean up */
		free(line);
	}

	return (0);
}
