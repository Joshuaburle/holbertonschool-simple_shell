#include "shell.h"

/**
 * _split_line - Splits a string into an array of tokens
 * @line: The string to split
 * Return: Array of tokens, or NULL on failure
 */
char **_split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n");
	}

	tokens[position] = NULL;
	return (tokens);
}

/**
 * execute_command - Executes a command
 * @command: The command to execute
 * @program_name: Name of the shell program (argv[0])
 * Return: 1 to continue, 0 to exit
 */
int execute_command(char *command, char *program_name)
{
	pid_t pid;
	int status;
	char **argv;

	if (command == NULL || is_empty_or_whitespace(command))
		return (1);

	/* Split command into arguments */
	argv = _split_line(command);
	if (argv == NULL)
		return (1);

	/* Check if it's an exit command */
	if (strcmp(argv[0], "exit") == 0)
	{
		/* Free allocated memory */
		free(argv);
		return (0);
	}

	/* Fork process */
	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(program_name);
			/* Free allocated memory before exit */
			free(argv);
			_exit(127);
		}
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("Error");
		free(argv);
		return (1);
	}
	else
	{
		/* Parent process waits for child */
		wait(&status);
	}

	/* Free allocated memory */
	free(argv);
	return (1);
}
