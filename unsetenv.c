#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * _unsetenv - Delete an environment variable
 * @name: Name of the environment variable to delete
 *
 * Return: 0 on success, -1 on error.
 */
int _unsetenv(const char *name)
{
	char **environ = __environ;
	int i = 0;
	size_t len = strlen(name);
	int j;

	while (environ[i] != NULL)
	{
		if (strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		{
/* Overwrites the matched environment variable */
		for (j = i; environ[j] != NULL; j++)
			environ[j] = environ[j + 1];
		return (0);
		}

		i++;
	}

	return (-1);
}
/**
 * main - Program entry
 *
 * Return: always 0 success
 */
int main(void)
{
	const char *var_name = "MY_VARIABLE";
	char *var_value_before, *var_value_after;
	int result;

	if (setenv(var_name, "some_value", 1) != 0)
	{
		write(STDOUT_FILENO, "Failed to set the environment variable.\n", 40);
		return (1);
	}

	var_value_before = getenv(var_name);
	write(STDOUT_FILENO, "Before unset: ", 15);
	write(STDOUT_FILENO, var_name, strlen(var_name));
	write(STDOUT_FILENO, "=", 1);
	write(STDOUT_FILENO, var_value_before, strlen(var_value_before));
	write(STDOUT_FILENO, "\n", 1);

	result = _unsetenv(var_name);
	if (result == 0)
	{
		write(STDOUT_FILENO, "Environment variable '", 23);
		write(STDOUT_FILENO, var_name, strlen(var_name));
		write(STDOUT_FILENO, "' unset successfully.\n", 22);
	}
	else
	{
		write(STDOUT_FILENO, "Failed to unset the environment variable.\n", 41);
		return (1);
	}

	var_value_after = getenv(var_name);
	write(STDOUT_FILENO, "After unset: ", 14);
	write(STDOUT_FILENO, var_name, strlen(var_name));
	write(STDOUT_FILENO, "=", 1);
	write(STDOUT_FILENO, var_value_after, strlen(var_value_after));
	write(STDOUT_FILENO, "\n", 1);

	return (0);
}
