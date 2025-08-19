#include "shell.h"

/**
 * main - Entry point of the shell
 * @argc: Number of arguments
 * @argv: Array of arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	int status = 1;

	(void)argc;

	/* Set up signal handling for Ctrl+C - simple inline handler */
	signal(SIGINT, SIG_IGN); /* Ignore Ctrl+C for now to save functions */

	while (status)
	{
		/* Call shell_loop which handles prompt, reading and execution */
		status = shell_loop(argv[0]);
	}

	return (0);
}
