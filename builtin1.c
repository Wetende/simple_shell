#include "shell.h"

/**
 * history_me - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @arg: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int history_me(data_t *arg)
{
	list_is_print(arg->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @arg: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(data_t *arg, char *str)
{
	char *x, c;
	int ret;

	x = my_strchr(str, '=');
	if (!x)
		return (1);
	c = *x;
	*x = 0;
	ret = del_node_index(&(arg->alias),
		take_index_node(arg->alias, begin_node_with(arg->alias, str, -1)));
	*x = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @arg: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(data_t *arg, char *str)
{
	char *x;

	x = my_strchr(str, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (unset_alias(arg, str));

	unset_alias(arg, str);
	return (insert_end_node(&(arg->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *x = NULL, *a = NULL;

	if (node)
	{
		x = my_strchr(node->str, '=');
		for (a = node->str; a <= x; a++)
			my_putchar(*a);
		my_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_me - mimics the alias builtin (man alias)
 * @arg: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int alias_me(data_t *arg)
{
	int i = 0;
	char *x = NULL;
	list_t *node = NULL;

	if (arg->argc == 1)
	{
		node = arg->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; arg->argv[i]; i++)
	{
		x = my_strchr(arg->argv[i], '=');
		if (x)
			set_alias(arg, arg->argv[i]);
		else
			print_alias(begin_node_with(arg->alias, arg->argv[i], '='));
	}

	return (0);
}
