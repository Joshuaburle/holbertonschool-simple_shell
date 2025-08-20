#include "shell.h"

/**
 * find_command - Finds the full path of a command (Tâche 0.2 - pas de PATH)
 * @command: The command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_command(char *command)
{
	/* Pour la tâche 0.2, on ne gère que les chemins absolus/relatifs */
	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	/* Pas de gestion du PATH pour la tâche 0.2 */
	return (NULL);
}

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
		return (NULL);

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
				return (NULL);
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
	char *full_path;

	if (command == NULL || is_empty_or_whitespace(command))
		return (1);

	/* Split command into arguments */
	argv = _split_line(command);
	if (argv == NULL)
		return (1);

	/* Check if it's an exit command */
	if (strcmp(argv[0], "exit") == 0)
	{
		free(argv);
		exit(0);
	}

	/* Find the full path of the command BEFORE forking */
	full_path = find_command(argv[0]);
	if (full_path == NULL)
	{
		/* Command not found - don't fork, just show error */
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, argv[0]);
		free(argv);
		return (1);
	}

	/* Now we know the command exists, so we can fork */
	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		argv[0] = full_path;
		if (execve(full_path, argv, environ) == -1)
		{
			perror(program_name);
			free(argv);
			free(full_path);
			_exit(127);
		}
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("Error");
		free(argv);
		free(full_path);
		return (1);
	}
	else
	{
		/* Parent process waits for child */
		wait(&status);
	}

	/* Free allocated memory */
	free(argv);
	free(full_path);
	return (1);
}
