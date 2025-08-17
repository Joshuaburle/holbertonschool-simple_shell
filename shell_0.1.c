#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * read_and_validate - Read user input and validate it
 * @interactive: Whether the shell is interactive
 * Return: Pointer to the validated line or NULL on EOF
 */
char *read_and_validate(int interactive)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	if (interactive)
		printf("#cisfun$ ");

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		if (interactive)
			printf("\n");
		return (NULL);
	}

	line[strcspn(line, "\n")] = '\0';

	if (strlen(line) == 0)
		return (read_and_validate(interactive));

	if (strlen(line) > 1024)
		return (read_and_validate(interactive));

	return (line);
}

/**
 * execute - Execute a command in a child process
 * @line: The command line to execute
 * Return: 0 on success, -1 on failure
 */
int execute(char *line)
{
	pid_t pid;
	extern char **environ;
	char *argv[2];

	if (strcmp(line, "exit") == 0)
		return (0);

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}

	if (pid == 0) /* Child process */
	{
		argv[0] = line;
		argv[1] = NULL;
		if (execve(line, argv, environ) == -1)
		{
			fprintf(stderr, "./shell: No such file or directory\n");
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	{
		if (wait(NULL) == -1)
		{
			perror("wait");
			return (-1);
		}
	}

	return (0);
}

/**
 * main - Entry point of the simple shell program
 * @void: No parameters
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		line = read_and_validate(interactive);
		if (!line)
			break;

		if (execute(line) == 0 && strcmp(line, "exit") == 0)
			break;
	}

	return (0);
}
