#include "shell.h"
int main(void)
{
    char *cmd = NULL;

    while (1)
    {
        get_command(&cmd);
        execute_command(cmd);
    }

    free(cmd);

    return 0;
}

