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

/* main.c */
int main(void);

/* exec.c*/
void execute_command(char *cmd);

/* fork.c */
pid_t fork(void);

/* pid.c*/
pid_t getpid(void);
/*prompt.c*/
void get_command(char **cmd);
/* ppid.c*/
pid_t getppid(void);

/* print.c */
void write_status_message(const char *message, int status);

#endif /* __MY_SHELL_H__*/

