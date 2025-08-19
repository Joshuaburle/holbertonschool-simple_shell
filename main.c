#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "shell.h"

/**
 * main - Point d'entrée principal du shell
 * @argc: Nombre d'arguments
 * @argv: Tableau des arguments
 * @env: Variables d'environnement
 * Return: 0 en cas de succès, 1 en cas d'erreur
 */
int main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;

	/* Démarrage du shell */
	shell_loop(env);

	return (0);
}
