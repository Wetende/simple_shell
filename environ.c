#include "shell.h"

/**
 * _myenv - function that prints the current environment
 * @info: Structure member containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(data_t *info)
{
	list_printed_string(data->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(data_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = _beginWith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initializes a new environment variable,
 *             or modifies an already existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(data_t *info)
{
	if (data->argc != 3)
	{
		eputs_me("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(data_t *info)
{
	int i;

	if (info->argc == 1)
	{
		eputs_me("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * increase_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int increase_env_list(data_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		insert_end_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
