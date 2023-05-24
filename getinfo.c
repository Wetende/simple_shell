#include "shell.h"

/**
 * deleteInformation - initializes data struct
 * @info: struct address
 */
void deleteInformation(data *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInformation - initializes data struct
 * @info: struct address
 * @av: argument vector
 */
void setInformation(data *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = my_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		_replaceAlias(info);
		replace_variable(info);
	}
}

/**
 * freeInformation - frees data struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeInformation(data *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			_freeList(&(info->env));
		if (info->history)
			_freeList(&(info->history));
		if (info->alias)
			_freeList(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		buff_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		my_putchar(BUF_FLUSH);
	}
}
