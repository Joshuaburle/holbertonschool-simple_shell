#include "shell.h"

/**
 * fork_and_exec - Forks process and executes command
 * @cmd_path: Path to the command
 * @argv: Array of command arguments
 * @program_name: Name of the shell program
 * Return: 1 on success, 0 on failure
 */
int fork_and_exec(char *cmd_path, char **argv, char *program_name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, argv, environ) == -1)
		{
			perror(program_name);
			free(argv);
			_exit(127);
		}
	}
	else if (pid < 0)
	{
		perror("Error");
		free(argv);
		return (0);
	}
	else
		wait(&status);
	return (1);
}

/**
 * execute_command - Executes a command with arguments
 * @command: The command line to execute
 * @program_name: Name of the shell program
 * Return: 1 to continue, 0 to exit
 */
int execute_command(char *command, char *program_name)
{
	char **argv;
	int argc;

	if (command == NULL || is_empty_or_whitespace(command))
		return (1);
	argv = parse_command(command, &argc);
	if (argv == NULL)
		return (1);
	if (strcmp(argv[0], "exit") == 0)
	{
		free(argv);
		exit(0);
	}
	if (strchr(argv[0], '/'))
	{
		if (access(argv[0], X_OK) != 0)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, argv[0]);
			free(argv);
			return (1);
		}
	}
	else
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, argv[0]);
		free(argv);
		return (1);
	}
	if (!fork_and_exec(argv[0], argv, program_name))
		return (0);
	free(argv);
	return (1);
}
