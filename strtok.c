#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/**
 * splt_strng - Split a string into words.
 * @str: The string to split.
 * @delimiters: The delimiters for split the string.
 * Return: An array of strings (words).
 */

char **splt_strng(char *str, const char *delimiters)
{
	char **words = NULL;
	char *token = NULL;
	int wc = 0;
	int index = 0;
	char *copy = strdup(str);

	token = strtok(copy, delimiters);
	while (token != NULL)
	{
		wc++;
		token = strtok(NULL, delimiters);
	}

	words = malloc((wc + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);

	token = strtok(copy, delimiters);
	while (token != NULL)
	{
		words[index] = strdup(token);
		if (words[index] == NULL)
		{
			while (index > 0)
				free(words[--index]);
			free(words);
			return (NULL);
		}

		index++;
		token = strtok(NULL, delimiters);
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

/**
 * main - program entry
 *Return: always 0 success
 */
int main(void)
{
	char str[] = "This is a test string, the functions should split it.";
	char delimiters[] = " ";
	char **words = splt_strng(str, delimiters);

	if (words == NULL)
	{
		perror("Error:Splitting failed.\n");
		return (1);
	}
	print_words(words);

	return (0);
}
