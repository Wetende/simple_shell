#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - function that implements execve system call
 * Return: Always 0
 */
int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr", NULL};

	write(1, "Before execve\n", 16);
	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("Error:");
	}
	write(1, "After execve\n", 16);

	return (0);
}
