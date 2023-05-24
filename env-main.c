#include "shell.h"

/**
 * main - Entry point
 * Return: 0 on success
 */
int main(void)
{
	char *cmd = NULL;
	char *args[BUFSIZE];
	int status;

	while (1)
	{
		get_command(&cmd);
		parse_command(cmd, args);
		if (!check_builtin(args))
		{
			fork_and_exec(args);
			waitpid(-1, &status, 0);
			handle_status(status);
		}
	}

	free(cmd);

	return (0);
}
