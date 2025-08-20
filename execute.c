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
	char *cmd_path;
	char *command_copy;

	if (command == NULL || is_empty_or_whitespace(command))
		return (1);

	/* Make a copy of the command before tokenizing */
	command_copy = strdup(command);
	if (!command_copy)
		return (1);

	/* Split command into arguments */
	argv = _split_line(command_copy);
	if (argv == NULL || argv[0] == NULL)
	{
		if (argv)
			free_tokens(argv);
		free(command_copy);
		return (1);
	}

	/* Check if it's an exit command */
	if (strcmp(argv[0], "exit") == 0)
	{
		free_tokens(argv);
		free(command_copy);
		return (0);
	}

	/* Check if it's env command */
	if (strcmp(argv[0], "env") == 0)
	{
		print_env();
		free_tokens(argv);
		free(command_copy);
		return (1);
	}

	/* For Simple shell 0.3+ - Handle PATH, don't fork if command doesn't exist */
	cmd_path = find_command(argv[0]);
	if (cmd_path == NULL)
	{
		/* Command not found - print error and don't fork */
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, argv[0]);
		free_tokens(argv);
		free(command_copy);
		return (1);
	}

	/* Debug: print arguments being passed to execve */
	printf("DEBUG: Executing %s with args: ", cmd_path);
	{
		int i;
		for (i = 0; argv[i]; i++)
			printf("[%s] ", argv[i]);
	}
	printf("\n");

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(cmd_path, argv, environ) == -1)
		{
			perror(program_name);
			free_tokens(argv);
			free(cmd_path);
			free(command_copy);
			_exit(127);
		}
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("Error");
		free_tokens(argv);
		free(cmd_path);
		free(command_copy);
		return (1);
	}
	else
	{
		/* Parent process waits for child */
		wait(&status);
	}

	/* Free allocated memory */
	free_tokens(argv);
	free(cmd_path);
	free(command_copy);
	return (1);
}

/**
 * print_env - Print environment variables
 * Return: void
 */
void print_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
