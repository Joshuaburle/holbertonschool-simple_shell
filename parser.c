#include "shell.h"
#include <string.h>

/**
 * parse_args - split input line into argv
 * @line: input buffer
 *
 * Return: argv array or NULL
 */
char **parse_args(char *line)
{
	char **argv;
	char *tok;
	int i = 0;

	argv = malloc(sizeof(char *) * (MAX_ARGS + 1));
	if (argv == NULL)
		return (NULL);

	tok = strtok(line, " \t\n");
	while (tok != NULL && i < MAX_ARGS)
	{
		argv[i++] = tok;
		tok = strtok(NULL, " \t\n");
	}

	if (i == 0)
	{
		free(argv);
		return (NULL);
	}

	argv[i] = NULL;
	return (argv);
}

/**
 * free_args - free argv array
 * @argv: argument vector
 */
void free_args(char **argv)
{
	free(argv);
}
