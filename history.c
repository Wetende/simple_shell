#include "shell.h"

/**
 * create_hist_list - adds entry to linked list history 
 * @args:  arguments
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int create_hist_list(data_t *args, char *buf, int linecount)
{
	list_t *node = NULL;

	if (args->history)
		node = args->history;
	insert_end_node(&node, buf, linecount);

	if (!args->history)
		args->history = node;
	return (0);
}
/**
 * take_hist_file - gets the history file
 * @args: arguments
 * Return: allocated string containg history file
 */
char *take_hist_file(data_t *args)
{
	char *buf, *dir;

	dir = _getenv(args, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (my_strlen(dir) + my_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	my_strcpy(buf, dir);
	my_strcat(buf, "/");
	my_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * put_hist - creates a file, or appends to an existing file
 * @args: the arguments
 * Return: 1 on success, else -1
 */
int put_hist(data_t *args)
{
	ssize_t fd;
	char *filename = take_hist_file(args);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = args->history; node; node = node->next)
	{
		putsfd_me(node->str, fd);
		putfd_me('\n', fd);
	}
	putfd_me(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * look_into_hist - reads history from file
 * @args: the arguments
 * Return: 0 otherwise
 */
int look_into_hist(data_t *args)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = take_hist_file(args);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			create_hist_list(args, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		create_hist_list(args, buf + last, linecount++);
	free(buf);
	args->histcount = linecount;
	while (args->histcount-- >= HIST_MAX)
		del_node_index(&(args->history), 0);
	number_again_hist(args);
	return (args->histcount);
}

/**
 * number_again_hist - numbers again linked list history 
 * @args: arguments
 * Return: the new histcount
 */
int number_again_hist(data_t *args)
{
	list_t *node = args->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (args->histcount = i);
}
