#include "shell.h"

/**
 *_atoi - string to integer conversation
 *@string: the string to be converted
 *Return:  1 true always 0
 */

int _atoi(char *string)
{
	int i, sign = 1, flag = 0, out_put;
	unsigned int result = 0;

	for (i = 0;  string[i] != '\0' && flag != 2; i++)
	{
		if (string[i] == '-')
			sign *= -1;

		if (string[i] >= '0' && string[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (string[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		out_put = -result;
	else
		out_put = result;

	return (out_put);
}


/**
 * responsive - returns true if in responsive mode
 * @info: address of struct
 * Return: 1 always 0
 */
int responsive(data *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


/**
 *isalpha_me - checks letters (alaphabetical characters)
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int isalpha_me(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * delimeter_me - checks for delimeter character
 * @ch: the value of character to be checked
 * @delim: the string of delimeter 
 * Return: return 1 always 0
 */
int delimeter_me(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

