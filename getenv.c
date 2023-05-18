#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
/**
 * _getenv - Gets an environment variable
 *
 * @name: The name of the environment variable
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(const char *name)
{
	char **environ = __environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		char *env_var = environ[i];
		int j = 0;

		while (env_var[j] != '\0' && env_var[j] != '=' && name[j] != '\0')
		{
			if (env_var[j] != name[j]
			break;
			j++;
		}
		if (env_var[j] == '=' && name[j] == '\0')
		return (env_var + j + 1);
		i++;

	}
	return (NULL);
}

int main(void)
{
	const char *var_name = "PATH";
	char *var_value = _getenv(var_name);

	if (var_value != NULL)
	{
		write(STDOUT_FILENO, var_name, strlen(var_name));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, var_value, strlen(var_value));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		const char *not_found_msg = "Environment variable '";
		const char *not_found_msg_suffix = "' not found.\n";

		write(STDOUT_FILENO, not_found_msg, strlen(not_found_msg));
		write(STDOUT_FILENO, var_name, strlen(var_name));
		write(STDOUT_FILENO, not_found_msg_suffix, strlen(not_found_msg_suffix));
	}

	return (0);
}
