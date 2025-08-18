#include "shell.h"

/**
 * main - Entry point of the shell.
 * Return: 0 on success.
 */
int main(void)
{
	char *line;
	int status = 1;

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
