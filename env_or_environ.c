#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

void printAddress(void *address)
{
	char buffer[20];
	sprintf(buffer, "%p\n", address);
	write(STDOUT_FILENO, buffer, strlen(buffer));
}

int main(int argc, char *argv[], char *env[])
{
	printAddress(env);
	printAddress(environ);

	if (env == environ)
	{
		write(STDOUT_FILENO, "env and environ are the same.\n", strlen("env and environ are the same.\n"));
	}
	else
	{
		write(STDOUT_FILENO, "env and environ are different.\n", strlen("env and environ are different.\n"));
	}

	return 0;
}
/**
 * To answer the question asked:
 * env and environ are the same
 * It doesn't make much sense because environ is a universal variable while
 * env is a parameter to the main function
 * Hence, the value of env may change but the value of environ is constant.
 */
