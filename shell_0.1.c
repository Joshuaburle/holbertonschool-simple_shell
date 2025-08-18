#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

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
	int interactive = isatty(STDIN_FILENO);
	char *argv[2];

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

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (strlen(line) == 0 || line[0] == ' ' || line[0] == '\t')
			continue;

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
				fprintf(stderr, "./shell: No such file or directory\n");
				exit(127);
			}
		}
		else
		{
			wait(NULL);
		}
	}

	free(line);
	return (0);
}
