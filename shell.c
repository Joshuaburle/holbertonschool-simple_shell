#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
	fflush(stdout);
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
	if (read_size > 0 && line[read_size - 1] == '
')
		line[read_size - 1] = '\0';

	return (line);
}

/**
 * is_empty_or_whitespace - Checks if line is empty or only whitespace
 * @line: The line to check
 * Return: 1 if empty/whitespace, 0 otherwise
 */
int is_empty_or_whitespace(char *line)
{
	int i;

	if (line == NULL || strlen(line) == 0)
		return (1);

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ' && line[i] != '	')
			return (0);
	}
	return (1);
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
			fprintf(stderr, "%s: 1: %s: not found
", program_name, command);
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
 * is_empty_or_whitespace - Checks if line is empty or only whitespace
 * @line: The line to check
 * Return: 1 if empty/whitespace, 0 otherwise
 */
int is_empty_or_whitespace(char *line)
{
	int i;

	if (line == NULL || strlen(line) == 0)
		return (1);

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
	}
	return (1);
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

	if (command == NULL || is_empty_or_whitespace(command))
		return (1);

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
