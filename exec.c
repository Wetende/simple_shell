#include "shell.h"
/**
 * fork_and_exec - function that forks and executes the command using execvp
 * @args: array of arguments to execute
 */
void fork_and_exec(char **args)
{
        pid_t pid;

        pid = fork();

        if (pid == -1)
        {
                perror("fork");
                exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
                execvp(args[0], args);
                perror(args[0]);
                exit(EXIT_FAILURE);
        }
}
