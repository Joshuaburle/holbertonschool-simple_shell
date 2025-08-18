#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - Entry point of the simple shell program
 * @void: No parameters
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	extern char **environ;
	int interactive = isatty(STDIN_FILENO);
	char *argv[2];
	int line_number = 1;

	while (1)
	{
		if (interactive)
			printf("#cisfun$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}

		/* Remove newline character */
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Skip empty lines and lines with only spaces/tabs */
		if (strlen(line) == 0 || line[0] == ' ' || line[0] == '\t')
		{
			line_number++;
			continue;
		}

		/* Handle exit command */
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			exit(0);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			continue;
		}

		if (pid == 0)
		{
			argv[0] = line;
			argv[1] = NULL;
			if (execve(line, argv, environ) == -1)
			{
				fprintf(stderr, "./shell: line %d: %s: command not found\n", line_number, line);
				exit(127);
			}
		}
		else
		{
			wait(NULL);
		}
		
		line_number++;
	}

	free(line);
	return (0);
}
