#include <stdio.h>
#include <unistd.h>

/**
 * main - a function that prints the parent process ID
 * Return: 0 on success
 */
int main(void)
{
	pid_t my_ppid;

	my_ppid = getppid();
	printf("%u\n", my_ppid);

	return (0);
}
