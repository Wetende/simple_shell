#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(data_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		deleteInformation(info);
		if (responsive(info))
			_puts("$ ");
		eputchar_me(BUF_FLUSH);
		r = read_input(info);
		if (r != -1)
		{
			setInformation(info, av);
			builtin_ret = get_builtin(info);
			if (builtin_ret == -1)
				get_command(info);
		}
		else if (responsive(info))
			my_putchar('\n');
		freeInformation(info, 0);
	}
return (0);	
}

/**
 * get_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int get_builtin(data_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_me},
		{"env", _myenv},
		{"help", help_me},
		{"history", history_me},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", cd_me},
		{"alias", alias_me},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (my_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * get_command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void get_command(data_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!delimeter_me(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = search_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkCommand(info);
	}
	else
	{
		if ((responsive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			forkCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_myerror_printing(info, "not found\n");
		}
	}
}

/**
 * forkCommand - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forkCommand(data_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, take_environ(info)) == -1)
		{
			freeInformation(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_myerror_printing(info, "Permission denied\n");
		}
	}
}
