#include "shell.h"

/* Gère Ctrl+C (réaffiche le prompt) */
static void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	display_prompt();
}

int main(int argc, char **argv)
{
	char *line = NULL;
	int status = 1;

	(void)argc;
	signal(SIGINT, sigint_handler);

	while (status)
	{
		if (isatty(STDIN_FILENO))
			display_prompt();

		line = read_line();
		if (line == NULL) /* Ctrl+D ou EOF */
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Exécute la ligne (0 => exit) */
		status = execute_command(line, argv[0]);

		free(line);
		line = NULL;

		if (status == 0)
			break;
	}
	return (0);
}
