#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * main - Find files in the PATH
 *
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	char *path, *token;
	int i;

	if (argc < 2)
	{
		write(STDOUT_FILENO, "Usage: ", 7);
		write(STDOUT_FILENO, argv[0], strlen(argv[0]));
		write(STDOUT_FILENO, " filename ...\n", 14);
		return (1);
	}

	path = getenv("PATH");
	if (path == NULL)
	{
		write(STDOUT_FILENO, "No PATH variable found.\n", 24);
		return (1);
	}

	token = strtok(path, ":");
	while (token != NULL)
	{
		for (i = 1; i < argc; i++)
		{
			char filepath[1024];
			snprintf(filepath, sizeof(filepath), "%s/%s", token, argv[i]);

			if (access(filepath, F_OK) == 0)
			{
				write(STDOUT_FILENO, filepath, strlen(filepath));
				write(STDOUT_FILENO, ": FOUND\n", 8);
			}
			else
			{
				write(STDOUT_FILENO, filepath, strlen(filepath));
				write(STDOUT_FILENO, ": NOT FOUND\n", 12);
			}
		}
		token = strtok(NULL, ":");
	}
	return (0);
}
