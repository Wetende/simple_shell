#include "shell.h"
/**
 * get_command - function that gets commands from stdin and generates output
 * @cmd: commands to get
 */
void get_command(char **cmd)
{
        size_t bufsize = 0;

        write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
        fflush(stdout);
        *cmd = NULL;

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
