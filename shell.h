#ifndef SHELL_H
#define SHELL_H
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>

extern char **environ;

char *read_line(void);
char **split_line(char *line);
int execute(char **args, char *argv, int cmd_count);
char *find_path(const char *cmd_name);
void print_env(void);
void free_args(char **args);
char *_getenv(const char *var_name);
void display_prompt(void);
char *read_input(void);
int execute_command(char *line);


void prompt(void);
int handle_builtin(char **args);

#endif
