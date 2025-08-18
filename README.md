# Simple Shell

A simple UNIX command line interpreter that mimics the behavior of the standard shell.

## Description

This project is a simple shell written in C that can execute basic commands. It displays a prompt, waits for user input, and executes the entered commands.

## Features

- Display a prompt and wait for user input
- Execute commands with absolute paths (e.g., `/bin/ls`)
- Handle errors when commands are not found
- Handle end-of-file condition (Ctrl+D)
- Handle Ctrl+C signal
- Support both interactive and non-interactive modes

## Compilation

The shell will be compiled with the following flags:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) exit
$
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

## Files

- `main.c`: Entry point of the shell
- `shell.c`: Core shell functions (prompt, input reading, etc.)
- `execute.c`: Command execution functions
- `shell.h`: Header file with function prototypes and includes
- `AUTHORS`: Contributors to the project
- `man_1_simple_shell`: Manual page for the shell
- `README.md`: This file

## Requirements

- All files compiled on Ubuntu 20.04 LTS using gcc
- Code follows Betty style guidelines
- No memory leaks
- Maximum 5 functions per file
- Header files are include guarded
- Only allowed system calls are used

## Authors

See AUTHORS file for a complete list of contributors.

## License

This project is part of the Holberton School curriculum.