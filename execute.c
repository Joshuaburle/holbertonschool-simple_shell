#include "shell.h"

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
		free_tokens(argv);
		return (0);
	}

	/* Find the full path of the command BEFORE forking */
	full_path = find_command(argv[0]);
	if (full_path == NULL)
	{
		/* Command not found - don't fork, just show error */
		fprintf(stderr, "%s: %s: command not found\n", program_name, argv[0]);
		free_tokens(argv);
		return (1);
	}

	/* Now we know the command exists, so we can fork */
	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(full_path, argv, environ) == -1)
		{
			perror(program_name);
			free_tokens(argv);
			free(full_path);
			_exit(127);
		}
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("Error");
		free_tokens(argv);
		free(full_path);
		return (1);
	}
	else
	{
		/* Parent process waits for child */
		wait(&status);
	}

	/* Free allocated memory */
	free_tokens(argv);
	free(full_path);
	return (1);
}
