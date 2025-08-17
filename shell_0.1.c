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

		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) == 0)
			continue;

		/* Vérifier que la ligne n'est pas trop longue */
		if (strlen(line) > 1024)
			continue;

		if (strcmp(line, "exit") == 0)
			break;

		pid = fork();
		if (pid == -1)
		{
			perror("Error");
			continue; /* Continuer au lieu de sortir */
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
				continue;
			}
		}
	}

	free(line);
	return (0);
}
