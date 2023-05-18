#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/**
 * main - fork example
 * Return: 0 on Success
 */
int main(void)
{
	pid_t pid;
	pid_t my_pid;

	printf("Before fork\n");
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (0);
	}
	printf("After fork\n");
	my_pid = getpid();
	printf("My pid is %u\n", my_pid);

	return (0);
}
