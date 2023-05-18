include "shell.h"
/**
 * fork - Create a new child process.
 *
 * Return: On success, the process ID of the child is returned in the parent,
 * and 0 is returned in the child. On failure, -1 is returned in the parent,
 * no child process is created, and errno is set appropriately.
 */
pid_t fork(void)
{
    pid_t pid;

    pid = fork(); /* Create a new child process */
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return pid;
}

