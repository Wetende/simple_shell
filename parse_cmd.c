#include "shell.h"

/**
 * parse_command - function that parses the command into an array of arguments
 * @cmd: command to parse
 * @args: array of arguments to store the result
 */
void parse_command(char *cmd, char **args)
{
        int argc = 0;
        char *token;

        token = strtok(cmd, " \t\n");
        while (token != NULL)
        {
                args[argc++] = token;
                token = strtok(NULL, " \t\n");
        }
        args[argc] = NULL;
}
/**
 * handle_status - function that handles the status of the child process
 * @status: status returned by waitpid
 */
void handle_status(int status)
{
        if (WIFEXITED(status))
        {
                write_status_message("Child exited with status ", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
                write_status_message("Child killed by signal ", WTERMSIG(status));
        }
}
