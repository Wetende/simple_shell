#include "shell.h"
void execute_command(char *cmd)
{
    char *args[BUFSIZE]; // Array of arguments
    int argc = 0;       // Number of arguments
    char *token;

    // Tokenize the command into arguments
    token = strtok(cmd, " \t\n");
    while (token != NULL)
    {
        args[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[argc] = NULL; // Set the last element of args to NULL

    if (strcmp(args[0], "exit") == 0)
    {
        exit(0); // Exit the shell program
    }

    pid_t pid;
    int status;

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
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            write_status_message("Child exited with status ", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            write_status_message("Child killed by signal ", WTERMSIG(status));
        }
    }
}
