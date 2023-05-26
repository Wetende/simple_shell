#include "shell.h"

/**
 **my_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *my_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * my_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @oldsize: byte size of previous block
 * @newsize: byte size of new block
 * Return: pointer to da ol'block nameen.
 */
void *my_realloc(void *ptr, unsigned int oldsize, unsigned int newsize)
{
	char *p;

	if (!ptr)
		return (malloc(newsize));
	if (!newsize)
		return (free(ptr), NULL);
	if (newsize == oldsize)
		return (ptr);

	p = malloc(newsize);
	if (!p)
		return (NULL);

	oldsize = oldsize < newsize ? oldsize : newsize;
	while (oldsize--)
		p[oldsize] = ((char *)ptr)[oldsize];
	free(ptr);
	return (p);
}
