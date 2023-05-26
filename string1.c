#include "shell.h"

/**
 * my_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *my_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}

/**
 * my_strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *my_strdup(const char *str)
{
	int len = 0;
	char *rt;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;
	rt = malloc(sizeof(char) * (len + 1));

	if (!rt)

		return (NULL);

	for (len++; len--;)

		rt[len] = *--str;

	return (rt);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		my_putchar(str[index]);
		index++;
	}
}

/**
 * my_putchar - writes ch to stdout
 * @ch: The character to print
 * Return: On success 1.
 */
int my_putchar(char ch)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buf, index);
		index = 0;
	}
	if (ch != BUF_FLUSH)
		buf[index++] = ch;
	return (1);
}
