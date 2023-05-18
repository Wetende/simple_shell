#include "shell.h"
/**
 * get_command - Prompt the user for a command and store it in cmd.
 * @cmd: Pointer to a string that will store the command entered by the user.
 */

void get_command(char **cmd)
{
    write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
    fflush(stdout);

    *cmd = NULL;
    size_t bufsize = 0;

    if (getline(cmd, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            write(STDOUT_FILENO, "\n", 1);
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }
}

