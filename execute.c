#include "shell.h"

/**
 * find_command - Finds the full path of a command
 * @command: The command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_command(char *command)
{
	char *path_env, *path_copy, *dir;
	char *full_path;

	/* 1. If command already contains a '/' */
	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0) /* executable */
		{
			return (strdup(command));
		}
		else
		{
			return (NULL);
		}
	}

	/* 2. Get PATH environment variable */
	path_env = getenv("PATH");
	if (!path_env || strlen(path_env) == 0)
	{
		/* Empty or NULL PATH - can't search in PATH directories */
		return (NULL);
	}

	/* 3. Make a modifiable copy */
	path_copy = strdup(path_env);
	if (!path_copy)
	{
		/* Return NULL instead of closing the shell */
		return (NULL);
	}

	/* 4. Search through each PATH directory */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		/* Dynamic allocation of exact size needed */
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		snprintf(full_path, strlen(dir) + strlen(command) + 2, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path); /* Return full_path directly, no need for strdup */
		}

		free(full_path); /* Free memory if command not found */
		dir = strtok(NULL, ":");
	}

	/* 5. Nothing found */
	free(path_copy);
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
	{
		/* Return NULL instead of closing the shell */
		return (NULL);
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
				/* Return NULL instead of closing the shell */
				return (NULL);
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
	char *cmd_path;

	if (command == NULL || is_empty_or_whitespace(command))
		return (1);

	/* Split command into arguments */
	argv = _split_line(command);
	if (argv == NULL || argv[0] == NULL)
	{
		if (argv)
			free(argv);
		return (1);
	}

	/* Check if it's an exit command */
	if (strcmp(argv[0], "exit") == 0)
	{
		free(argv); /* Free tokens array */
		exit(0);
	}

	/* For Simple shell 0.3+ - Handle PATH, don't fork if command doesn't exist */
	cmd_path = find_command(argv[0]);
	if (cmd_path == NULL)
	{
		/* Command not found - print error and don't fork */
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, argv[0]);
		free(argv); /* Free tokens array */
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(cmd_path, argv, environ) == -1)
		{
			perror(program_name);
			free(argv); /* Free tokens array */
			free(cmd_path); /* Free command path */
			_exit(127);
		}
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("Error");
		free(argv); /* Free tokens array */
		free(cmd_path); /* Free command path */
		return (1);
	}
	else
	{
		/* Parent process waits for child */
		wait(&status);
	}

	/* Free allocated memory */
	free(argv); /* Free tokens array */
	free(cmd_path); /* Free command path */
	return (1);
}
