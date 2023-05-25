#include "shell.h"


/**
 *putsfd_me - prints string 
 * @str: the string value
 * @fd: the where to to write(filediscriptor)
 *
 * Return: the number of chars put
 */
int putsfd_me(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += putfd_me(*str++, fd);
	}
	return (i);
}

/**
 *eputs_me - prints string input
 * @str: value of the string
 *
 * Return: return nothing
 */
void eputs_me(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		eputchar_me(str[i]);
		i++;
	}
}

/**
 * eputchar_me - writes ch to stderr
 * @ch: The character to be printed
 * Return: On success 1. On error, -1 is returned, 
 */
int eputchar_me(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 * putfd_me - writes ch to specified fd
 * @ch: The character to e printed
 * @fd: The filedescriptor to written to
 * Return: On success 1. On error, -1.
 */
int putfd_me(char ch, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}
