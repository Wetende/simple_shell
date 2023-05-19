#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "my_header.h"

/**
 * print_pid_and_fork - Print the process ID and fork a child process
 */
void print_pid_and_fork(void)
{
	printf("My pid is %u\n", getpid());
	if (fork() == 0)
	{
		printf("(%u) Nooooooooo!\n", getpid());
	}
	else
	{
		printf("(%u) %u, I am your father\n", getpid(), getppid());
	}
}

/**
 * execute_ls - Execute the ls command with arguments
 */
void execute_ls(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr", NULL};
	write(1, "Before execve\n", 16);
	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("Error:");
	}
	write(1, "After execve\n", 16);
}

/**
 * get_and_delete_env_vars - Get the value of the PATH environment variable
 * and delete the HOME environment variable
 */
void get_and_delete_env_vars(void)
{
	char *env_var = NULL;

	env_var = _getenv("PATH");
	if (env_var == NULL)
	{
		write(1, "PATH not found\n", 15);
	}
	else
	{
		write(1, "PATH: ", 6);
		write(1, env_var, strlen(env_var));
		write(1, "\n", 1);
	}

	if (_unsetenv("HOME") == -1)
	{
		write(1, "Failed to delete HOME\n", 22);
	}
	else
	{
		write(1, "Deleted HOME\n", 13);
	}
}

/**
 * prompt_and_print_input - Prompt for input and print it on the next line
 *
 * Return: The input string or NULL on error.
 */
char *prompt_and_print_input(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read = 0;

	get_input();

	read = getline(&input, &len, stdin);
	if (read == -1)
	{
		perror("Error:");
		return (NULL);
	}
	else
	{
		input[read - 1] = '\0';
		write(1, "Input: ", 7);
		write(1, input, read - 1);
		write(1, "\n", 1);

        return (input);
    }
}

/**
 * split_and_print_words - Split the input into words and print them
 *
 * @input: The input string to split.
 */
void split_and_print_words(char *input)
{
	char **words = NULL;

	write(1, "Words:\n", 7);
    words = split_string(input, " ");
    print_arguments(words);

    /* Free the allocated memory */
    free(words);
}

/**
 * main - The program entry point
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input = NULL;

	print_pid_and_fork();
	execute_ls();
	get_and_delete_env_vars();
	input = prompt_and_print_input();
	if (input != NULL)
    {
        split_and_print_words(input);

        /* Free the allocated memory */
        free(input);
    }

	return (0);
}

