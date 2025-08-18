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
	char *argv[2];

	if (command == NULL || is_empty_or_whitespace(command))
		return (1);

	/* Handle exit command */
	if (strcmp(command, "exit") == 0)
		return (0);

	/* Fork process */
	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		argv[0] = command;
		argv[1] = NULL;
		if (execve(command, argv, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, command);
			_exit(127);
		}
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("Error");
		return (1);
	}
	else
	{
		/* Parent process waits for child */
		wait(&status);
	}

	return (1);
}
