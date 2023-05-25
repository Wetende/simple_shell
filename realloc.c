#include "shell.h"

/**
 * ffree - frees a string of strings
 * @str_str: string of strings
 */
void ffree(char **str_str)
{
	char **a = str_str;

	if (!str_str)
		return;
	while (*str_str)
		free(*str_str++);
	free(a);
}

/**
 * my_memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill the memory area with
 * @n: the amount of bytes to be filled
 * Return: (*s) pointer to the memory area
 */
char *my_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * my_realloc - reallocates a block of memory
 * @ptr: a pointer to previously malloc-ed block
 * @old_size: byte size of old block
 * @new_size: byte size of current block
 *
 * Return: pointer to the old block of memory.
 */
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
