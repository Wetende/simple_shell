#include "shell.h"

/**
 * _beginWith - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *_beginWith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * my_strlen - returns string length
 * @string: the string
 * Return: length of string
 */
int my_strlen(char *string)
{
	int index = 0;

	if (!string)
		return (0);

	while (*string++)
		index++;
	return (index);
}

/**
 * my_strcmp - compare two strings.
 * @string1: string one
 * @string2: string two
 * Return: always 0
 */
int my_strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * my_strcat - concatenates two strings
 * @dest: destination buffer
 * @src: source buffer
 * Return: pointer of dest buffer
 */
char *my_strcat(char *dest, char *src)
{
	char *rt = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (rt);
}
