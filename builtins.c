#include "shell.h"
/**
 * check_builtin - function that checks for built-in commands and executes them
 * @args: array of arguments to check
 * Return: 1 if a built-in command is executed, 0 otherwise
 */
int check_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		exit(0);
		return (1);
	}

	return (0);
}
