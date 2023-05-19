#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "my_header.h"
/**
 * _getenv - Gets an environment variable
 *
 * @name: The name of the environment variable
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(const char *name)
{
	char *environ = NULL;
	int i = 0;
	char env_var = '\0';
	int j = 0;
	char *value = NULL;

	/* Get the environment variable value from the getenv function */
	environ = getenv(name);

	if (environ == NULL)
	{
		return (NULL);
	}

	while (environ[i] != '\0')
	{
		env_var = environ[i];
		j = 0;

		while (env_var != '\0' && env_var != '=' && name[j] != '\0')
		{
			if (env_var != name[j])
				break;
			j++;
		}
		if (env_var == '=' && name[j] == '\0')
		{
			value = strdup(environ + j + 1);
			if (value == NULL)
			{
				perror("Error:");
				return (NULL);
			}
			return (value);
		}
		i++;
	}
	return (NULL);
}

/**
 * print_arguments - print all the arguments
 * @argc: the number of arguments
 * @argv: value of arguments
 */

void print_arguments(char **words)
{
	int i;

	for (i = 0; words[i] != NULL; i++)
	{

		size_t arg_length = strlen(words[i]);

		write(STDOUT_FILENO, words[i], arg_length);
		write(STDOUT_FILENO, " ", 1);
	}


write(STDOUT_FILENO, "\n", 1);
}

/**
 * get_input - Prompts for input, reads the command,
 * and prints it on the next line.
 */

void get_input(void)
{

	char ch;
	char command[256];
	int index = 0;

	write(STDOUT_FILENO, "$ ", 2);
	while (read(STDIN_FILENO, &ch, 1) != -1)
	{
		command[index] = ch;

		if (ch == '\n')
			break;
		index++;
	}
	write(STDOUT_FILENO, command, index);
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * split_stirng - Split a string into words.
 * @str: The string to split.
 * @delimiters: The delimiters for splitting the string.
 * Return: An array of strings (words).
 */
char **split_stirng(char *str, const char *delimiters)
{
	char **words = NULL;
	char *token = NULL;
	int wc = 0;
	int index = 0;
	char *copy = strdup(str);
	char *saveptr = NULL;

	if (copy == NULL)
	{
		perror("Error:");
		return (NULL);
	}

	token = strtok_r(copy, delimiters, &saveptr);
	while (token != NULL)
	{
		wc++;
		token = strtok_r(NULL, delimiters, &saveptr);
	}
	free(copy);

	copy = strdup(str);
	if (copy == NULL)
	{
		perror("Error:");
		return (NULL);
	}

	token = strtok_r(copy, delimiters, &saveptr);
	while (token != NULL)
    {
        words[index] = strdup(token);
        if (words[index] == NULL)
        {
            while (index > 0)
                free(words[--index]);
            free(words);
            free(copy);
            return (NULL);
        }
        index++;
        token = strtok_r(NULL, delimiters, &saveptr);
    }
    words[index] = NULL;
    free(copy);

    return (words);
}

/**
 * print_words - Print the words in the array.
 * @words: The array of words.
 */
void print_words(char **words)
{
	int index = 0;

	while (words[index] != NULL)
	{
        write(1, words[index], strlen(words[index]));
        write(1, "\n", 1);
        index++;
    }

    write(1, "NULL\n", 5);
}

