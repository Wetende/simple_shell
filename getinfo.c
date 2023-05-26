#include "shell.h"

/**
 * deleteInformation - initializes data_t struct
 * @information: struct address
 */
void deleteInformation(data_t *information)
{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}

/**
 * setInformation - initializes data_t struct
 * @information: struct address
 * @av: argument vector
 */
void setInformation(data_t *information, char **av)
{
	int i = 0;

	information->fname = av[0];
	if (information->arg)
	{
		information->argv = strtow(information->arg, " \t");
		if (!information->argv)
		{

			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = my_strdup(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (i = 0; information->argv && information->argv[i]; i++)
			;
		information->argc = i;

		_replaceAlias(information);
		replace_variable(information);
	}
}

/**
 * freeInformation - frees data_t struct fields
 * @information: struct address
 * @all: true if freeing all fields
 */
void freeInformation(data_t *information, int all)
{
	ffree(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (all)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			_freeList(&(information->env));
		if (information->history)
			_freeList(&(information->history));
		if (information->alias)
			_freeList(&(information->alias));
		ffree(information->environ);
			information->environ = NULL;
		buff_free((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		my_putchar(BUF_FLUSH);
	}
}
