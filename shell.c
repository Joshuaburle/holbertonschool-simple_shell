#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * read_line - Reads a line from stdin
 * Return: Pointer to the line, or NULL on EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_size;

	read_size = getline(&line, &len, stdin);
	if (read_size == -1)
	{
		free(line);
		return (NULL);
	}

	/* Remove newline character */
	if (read_size > 0 && line[read_size - 1] == '\n')
		line[read_size - 1] = '\0';

	return (line);
}

/**
 * execute_command - Executes a command
 * @command: The command to execute
 * Return: 1 to continue, 0 to exit
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	if (command == NULL || strlen(command) == 0)
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
			fprintf(stderr, "./shell: No such file or directory\n");
			exit(127);
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
		wait(&status);
	}

	return (1);
}
