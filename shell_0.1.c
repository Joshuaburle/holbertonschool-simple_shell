#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

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
		line[strcspn(line, "\n")] = '\0';

		/* Skip empty lines */
		if (strlen(line) == 0)
			continue;

		/* Check if command exists and is executable */
		struct stat st;
		if (stat(line, &st) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", line);
			continue;
		}
		
		if (!(st.st_mode & S_IXUSR))
		{
			fprintf(stderr, "%s: Permission denied\n", line);
			continue;
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
				perror(line);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(NULL) == -1)
			{
				perror("wait");
				continue;
			}
		}
	}

	free(line);
	return (0);
}
