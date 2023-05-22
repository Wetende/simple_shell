
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>

#define BUFSIZE 1024
#define PROMPT "$ "

/* Function prototypes */
void get_command(char **cmd);
void write_status_message(const char *message, int status);
void parse_command(char *cmd, char **args);
int check_builtin(char **args);
void fork_and_exec(char **args);
void handle_status(int status);
void env_builtin(int status);
#endif /* SHELL_H */

