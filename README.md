# 🐚 holbertonschool-simple_shell

A custom implementation of a simple UNIX shell in C language, developed as part of the Holberton School curriculum.

## 📋 Table of Contents

- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Supported Commands](#supported-commands)
- [Project Structure](#project-structure)
- [Compilation](#compilation)
- [Testing](#testing)
- [Usage Examples](#usage-examples)
- [Internal Functioning](#internal-functioning)
- [Authors](#authors)

## 🎯 Description

This project implements a simple UNIX shell (command interpreter) capable of executing programs, managing built-in commands, and navigating through the file system. The shell supports command execution via PATH, argument handling, essential built-in commands, and proper exit code management.

## ✨ Features

- ✅ Interactive and non-interactive modes
- ✅ Command execution with PATH search and validation
- ✅ Command argument support with proper parsing
- ✅ Built-in commands (`exit`, `env`)
- ✅ Robust error handling with appropriate exit codes
- ✅ Custom prompt (#cisfun$ )
- ✅ Proper memory management (no leaks)
- ✅ Betty coding standards compliant
- ✅ Support for absolute and relative paths
- ✅ Exit code propagation and management
- ✅ Custom environment variable handling

## 🚀 Installation

```bash
# Clone the repository
git clone https://github.com/Joshuaburle/holbertonschool-simple_shell.git

# Navigate to the folder
cd holbertonschool-simple_shell

# Compile the project
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell
```

## 💻 Usage

### Interactive mode
```bash
$ ./shell
#cisfun$ /bin/ls
AUTHORS  README.md  execute.c  shell  main.c  shell.c  shell.h
#cisfun$ ls -l
total 32
-rw-r--r-- 1 user user  165 Aug 20 10:00 AUTHORS
-rw-r--r-- 1 user user 3214 Aug 20 10:00 README.md
#cisfun$ exit
$
```

### Non-interactive mode
```bash
$ echo "/bin/ls" | ./shell
AUTHORS  README.md  execute.c  shell  main.c  shell.c  shell.h

$ echo "ls -l /tmp" | ./shell
total 8
drwx------ 2 user user 4096 Aug 20 09:00 temp_folder

$ printf "echo hello\nexit 5\n" | ./shell; echo "Exit code: $?"
hello
Exit code: 5
```

## 📝 Supported Commands

### External commands
All commands available in the system PATH:
- `ls`, `cat`, `grep`, `ps`, `who`, etc.
- Commands with absolute paths: `/bin/ls`, `/usr/bin/env`
- Commands with relative paths: `./script.sh`
- Commands with arguments: `ls -la`, `grep pattern file`

### Built-in commands

| Command | Description | Example | Exit Code |
|---------|-------------|---------|-----------|
| `exit` | Exit the shell | `exit` | Last command's exit code |
| `exit [n]` | Exit with specific code | `exit 5` | Specified code (n) |
| `env` | Display environment variables | `env` | 0 on success |

## 📁 Project Structure

```
holbertonschool-simple_shell/
├── shell.h              # Main header file with prototypes
├── main.c               # Program entry point and main loop
├── shell.c              # User interface and I/O functions
├── execute.c            # Command execution and built-ins logic
├── path.c               # PATH search and command resolution
├── split.c              # Command line argument parsing
├── man_1_simple_shell   # Manual page
├── AUTHORS              # Contributors list
└── README.md            # This file
```

### File descriptions

#### `shell.h`
Contains all function declarations, necessary includes, and prototypes.

#### `main.c`
Implements the main shell loop:
- Interactive/non-interactive mode handling
- User command reading
- Execution function calls

#### `execute.c`
Contains execution logic:
- PATH command search
- Process fork and exec
- Execution error handling

#### `shell.c`
User interface functions:
- Prompt display
- Command line reading
- Input validation

## 🔧 Compilation

The project uses the following compilation flags to ensure code quality:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Flags used:
- `-Wall` : Enable all major warnings
- `-Werror` : Treat warnings as errors
- `-Wextra` : Enable additional warnings
- `-pedantic` : Strictly adhere to C standard
- `-std=gnu89` : Use GNU C89 standard

## ✅ Testing

### Interactive tests
```bash
$ ./hsh
#cisfun$ ls
AUTHORS  README.md  execute.c  hsh  main.c  shell.c  shell.h
#cisfun$ /bin/pwd
/home/user/holbertonschool-simple_shell
#cisfun$ exit
```

### Non-interactive tests
```bash
$ echo "ls -l" | ./hsh
$ echo "pwd" | ./hsh
$ echo "exit" | ./hsh
```

## 🔍 Usage Examples

### Example 1: Simple commands
```bash
#cisfun$ ls
AUTHORS  README.md  execute.c  shell  main.c  shell.c  shell.h
#cisfun$ pwd
/home/user/holbertonschool-simple_shell
#cisfun$ whoami
user
```

### Example 2: Commands with arguments
```bash
#cisfun$ ls -la
total 56
drwxr-xr-x 3 user user  4096 Aug 20 10:00 .
drwxr-xr-x 5 user user  4096 Aug 20 09:30 ..
-rw-r--r-- 1 user user   165 Aug 20 10:00 AUTHORS
```

### Example 3: Absolute and relative paths
```bash
#cisfun$ /bin/echo "Hello World"
Hello World
#cisfun$ ./shell
#cisfun$ echo "Nested shell"
Nested shell
#cisfun$ exit
```

### Example 4: Built-in commands
```bash
#cisfun$ env | head -3
PATH=/usr/bin:/bin
HOME=/home/user
USER=user
#cisfun$ exit 42
$ echo $?
42
```

### Example 5: Error handling
```bash
#cisfun$ invalidcommand
hsh: 1: invalidcommand: command not found
#cisfun$ /bin/nonexistent
hsh: 1: /bin/nonexistent: No such file or directory
#cisfun$ ./nonexecutable
hsh: 1: ./nonexecutable: Permission denied
```

## 🛠️ Internal Functioning

### Main algorithm:

1. **Initialization**: Shell setup and mode verification
2. **Main loop**: 
   - Prompt display (interactive mode)
   - Command reading
   - Argument parsing
3. **Execution**:
   - Built-in verification
   - PATH search
   - Fork and execution
4. **Error handling**: Appropriate error messages
5. **Cleanup**: Memory liberation

### PATH management:
- Sequential search in PATH directories
- Execution permission verification
- Support for absolute and relative paths

### Memory management:
- Dynamic allocation for arguments
- Systematic resource liberation
- No memory leaks

## 🤝 Contribution

This project is part of the Holberton School curriculum. Contributions are limited to project students.

## 📄 License

This project is developed for educational purposes as part of Holberton School.

## 👥 Authors

- **Joshua Burle** - *Lead Developer* - [GitHub](https://github.com/Joshuaburle)
- **Mohamed Jebabli** - *Lead Developer* - 

## 📖 Man Page

To view the complete manual page for the simple shell:

```bash
man ./man_1_simple_shell
```

The manual page includes detailed information about:
- Command syntax and options
- Built-in commands documentation
- Environment variables usage
- Examples for both interactive and non-interactive modes
- Error handling and exit status codes

### Manual Page Preview

![Man Page 1/3](image/Man%20page%201-3.png)
*Figure 1: Manual page header and description*

![Man Page 2/3](image/Man%20page%202-3.png)
*Figure 2: Built-in commands and examples*

![Man Page 3/3](image/Man%20page%203-3.png)
*Figure 3: Error handling and author information*

---

*Project developed for Holberton School - Simple Shell*
