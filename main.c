#include "shell.h"
#include <signal.h>

/**
 * sigint_handler - Handles Ctrl+C signal
 * @sig: Signal number
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * main - Entry point of the shell.
 * Return: 0 on success.
 */
int main(void)
{
	char *line;
	int status = 1;

	/* Set up signal handling for Ctrl+C */
	signal(SIGINT, sigint_handler);

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
		status = execute_command(line);

		/* Clean up */
		free(line);
	}

	return (0);
}
