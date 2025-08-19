#include "shell.h"

/**
 * create_process - Crée un nouveau processus
 * Return: PID du processus créé, ou -1 en cas d'échec
 */
pid_t create_process(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		return (-1);
	}
	return (pid);
}

/**
 * wait_for_child - Attend la fin d'un processus enfant
 * @pid: PID du processus à attendre
 * Return: 0 en cas de succès, -1 en cas d'échec
 */
int wait_for_child(pid_t pid)
{
	int status;

	(void)pid;
	if (wait(&status) == -1)
	{
		perror("Error");
		return (-1);
	}
	return (0);
}
