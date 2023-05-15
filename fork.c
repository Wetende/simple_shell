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

	write(STDOUT_FILENO, "Before fork\n", 12);
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (0);
	}
	write(STDOUT_FILENO, "After fork\n", 12);

	my_pid = getpid();
	write(1, "My pid is ", 12);
	return (0);
}
