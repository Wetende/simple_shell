#include <stdio.h>
#include <unistd.h>

/**
 * main - Print environment using environ
 *
 * Return: Always 0.
 */
int main(void)
{
    extern char **environ;
    int i = 0;

    while (environ[i] != NULL)
    {
        char *env_var = environ[i];
        size_t len = 0;
        while (env_var[len] != '\0')
            len++;

        write(STDOUT_FILENO, env_var, len);
        write(STDOUT_FILENO, "\n", 1);

        i++;
    }

    return 0;
}

