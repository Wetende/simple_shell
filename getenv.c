#include "shell.h"

/**
 * take_environ - returns the string array copy of our environ
 * @information: Structure containing potential arguments.
 * Return: Always 0
 */
char **take_environ(data_t *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = list_str(information->env);
		information->env_changed = 0;
	}

	return (information->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @information: Structure containing potential arguments.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(data_t *information, char *var)
{
	list_t *node = information->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = _beginWith(node->str, var);
		if (p && *p == '=')
		{
			information->env_changed = del_node_index(&(information->env), i);
			i = 0;
			node = information->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (information->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 * @information: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(data_t *information, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(my_strlen(var) + my_strlen(value) + 2);
	if (!buf)
		return (1);
	my_strcpy(buf, var);
	my_strcat(buf, "=");
	my_strcat(buf, value);
	node = information->env;
	while (node)
	{
		p = _beginWith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			information->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	insert_end_node(&(information->env), buf, 0);
	free(buf);
	information->env_changed = 1;
	return (0);
}
