#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char **_split_line(char *line);
char *find_command(char *command);

#endif
