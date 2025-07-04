# Simple Shell - Project

This project is a simple UNIX command-line interpreter (shell), developed as part of the Holberton School curriculum. It replicates basic functionality of the UNIX shell in C.

## 📌 Description

The shell provides:

- A prompt (`$`) where the user can enter commands.
- Execution of commands with their full path (e.g., `/bin/ls`).
- Search for commands using the `PATH` environment variable.
- Support for built-in commands: `exit` and `env`.
- Basic error handling for commands not found or inaccessible.

> ⚠️ Note: This shell does **not** support piping, redirection, semicolons, or command arguments beyond a single word.

## 🛠️ Compilation

To compile the program, run:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
