#include "shell.h"

/**
 * listLength - determines length of linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t listLength(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_str - array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_str(list_t *head)
{
	list_t *node = head;
	size_t i = listLength(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(my_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = my_strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * list_is_print - prints all elements of a list_t linked list
 * @hd: pointer first node
 * Return: size of list
 */
size_t list_is_print(const list_t *hd)
{
	size_t index = 0;

	while (hd)
	{
		_puts(num_conversion(hd->num, 10, 0));
		my_putchar(':');
		my_putchar(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		index++;
	}
	return (index);
}

/**
 * begin_node_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: 0
 */
list_t *begin_node_with(list_t *node, char *prefix, char c)
{
	char *pointer = NULL;

	while (node)
	{
		pointer = _beginWith(node->str, prefix);
		if (pointer && ((c == -1) || (*pointer == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * take_index_node - takes the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t take_index_node(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
