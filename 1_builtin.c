#include "shell.h"

/**
 * history_me - displays the history list, one command by line
 * @information: Structure containing potential arguments.
 *  Return: Always 0
 */
int history_me(data_t *information)
{
	list_is_print(information->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @information: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(data_t *information, char *str)
{
	char *p, c;
	int ret;

	p = my_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = del_node_index(&(information->alias),
		take_index_node(information->alias,
			begin_node_with(information->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @information: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(data_t *information, char *str)
{
	char *p;

	p = my_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(information, str));

	unset_alias(information, str);
	return (insert_end_node(&(information->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = my_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			my_putchar(*a);
		my_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_me - mimics the alias builtin (man alias)
 * @information: Structure containing potential arguments.
 *  Return: Always 0
 */
int alias_me(data_t *information)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (information->argc == 1)
	{
		node = information->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; information->argv[i]; i++)
	{
		p = my_strchr(information->argv[i], '=');
		if (p)
			set_alias(information, information->argv[i]);
		else
			print_alias(begin_node_with(information->alias, information->argv[i], '='));
	}

	return (0);
}
