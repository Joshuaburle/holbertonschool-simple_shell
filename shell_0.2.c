#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    extern char **environ;
    int interactive = isatty(STDIN_FILENO);
    char **argv;

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

        /* Supprime le retour à la ligne */
        line[strcspn(line, "\n")] = '\0';

        /* Built-in exit */
        if (strcmp(line, "exit") == 0)
            break;

        /* Découpe la ligne en arguments */
        argv = _split_line(line);
        if (!argv)
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) /* enfant */
        {
            if (execve(argv[0], argv, environ) == -1)
            {
                perror("execve");
            }
            exit(EXIT_FAILURE);
        }
        else /* parent */
        {
            wait(NULL);
        }

        free(argv); /* libère le tableau des arguments */
    }

    free(line);
    return 0;
}
