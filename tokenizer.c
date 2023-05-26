#include "shell.h"
/**
 * **my_strtow2 - splits a string into words
 * @str: the string to be inputed
 * @d: delimeter
 * Return: 1 always 0
 */
char **my_strtow2(char *str, char d)
{
	int i, j, k, m, number_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			number_words++;
	if (number_words == 0)
		return (NULL);
	s = malloc((1 + number_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < number_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}


/**
 * **strtow - splits a string into words
 * @str: input string
 * @d: delimeter
 * Return: return 1 always 0 on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, number_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!delimeter_me(str[i], d) && (delimeter_me(str[i + 1], d) || !str[i + 1]))
			number_words++;

	if (number_words == 0)
		return (NULL);
	s = malloc((1 + number_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < number_words; j++)
	{
		while (delimeter_me(str[i], d))
			i++;
		k = 0;
		while (!delimeter_me(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

