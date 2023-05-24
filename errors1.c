#include "shell.h"

/**
 * num_conversion - converts function
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *num_conversion(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do	{
		*--pointer = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}

/**
 * _erratoi - changes string to integer
 * @string: value of string
 * Return: 0 if no numbers in string,-1 on error
 */
int _erratoi(char *string)
{
	int i = 0;
	unsigned long int result = 0;

	if (*string == '+')
		string++;  
	for (i = 0;  string[i] != '\0'; i++)
	{
		if (string[i] >= '0' && string[i] <= '9')
		{
			result *= 10;
			result += (string[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _myerror_printing - writes error message
 * @args: the parameter & return args struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers, -1 on errorc
 */
void _myerror_printing(data *args, char *estr)
{
	eputs_me(args->fname);
	eputs_me(": ");
	_myprint(args->line_count, STDERR_FILENO);
	eputs_me(": ");
	eputs_me(args->argv[0]);
	eputs_me(": ");
	eputs_me(estr);
}

/**
 * _myprint - prints a decimal number
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: characters(numbers) printed
 */
int _myprint(int input, int fd)
{
	int (*_my_putchar)(char) = my_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		_my_putchar = eputchar_me;
	if (input < 0)
	{
		_abs_ = -input;
		_my_putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			_my_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	_my_putchar('0' + current);
	count++;

	return (count);
}


/**
 * rm_comments - replaces '#' with '\0'
 * @buf: string address to modify
 * Return: Always 0;
 */
void rm_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
