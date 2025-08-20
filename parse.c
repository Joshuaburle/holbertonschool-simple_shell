#include "shell.h"

/**
 * parse_command - Parses command line into arguments
 * @command: The command line to parse
 * @argc: Pointer to store argument count
 * Return: Array of arguments, or NULL on failure
 */
char **parse_command(char *command, int *argc)
{
	char **argv;
	char *token;
	int i;

	/* Count arguments first */
	*argc = 0;
	token = strtok(strdup(command), " \t");
	while (token != NULL)
	{
		(*argc)++;
		token = strtok(NULL, " \t");
	}

	/* Allocate argv array */
	argv = malloc((*argc + 1) * sizeof(char *));
	if (!argv)
		return (NULL);

	/* Parse command and arguments */
	token = strtok(strdup(command), " \t");
	i = 0;
	while (token != NULL && i < *argc)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}
	argv[*argc] = NULL;

	return (argv);
}
