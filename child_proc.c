#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - Entry point
 * Return: 0 on success
 */
int main(void)
{
	pid_t pid;

	pid = fork();

	if (pid == 0)
	{
		printf("Child process: PID = %d\n", getpid());
	}
	else if (pid > 0)
	{
		printf("Parent process: Child's PID = %d\n", pid);
	}
	else
	{
		printf("Forking failed.\n");
	}

	return (0);
}
