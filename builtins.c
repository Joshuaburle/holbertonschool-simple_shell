#include "shell.h"
#include <string.h>

/**
 * handle_exit - handle exit builtin
 * @argv: argument vector
 * @line: input line buffer
 * @last_status: last command exit status
 *
 * Return: 1 if shell should exit, 0 otherwise
 */
int handle_exit(char **argv, char *line, int last_status)
{
	if (argv[0] && strcmp(argv[0], "exit") == 0)
	{
		free_args(argv);
		free(line);
		exit(last_status);
	}
	return (0);
}

/**
 * handle_env - print current environment
 * @argv: argument vector
 *
 * Return: 1 if env was handled, 0 otherwise
 */
int handle_env(char **argv)
{
	int i;

	if (argv[0] && strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}
	return (0);
}
