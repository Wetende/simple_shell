#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(data_t *data, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*buff_free((void **)data->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_sigint);

		r = getline(buf, &len_p, stdin);

		r = _getline(data, buf, &len_p);

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			data->linecount_flag = 1;
			rm_comments(*buf);
			create_hist_list(data, *buf, data->histcount++);
			/* if (my_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				data->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * read_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read successfully
 */
ssize_t read_input(data_t *data)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(data->arg), *p;

	my_putchar(BUF_FLUSH);
	r = input_buf(data, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		_checkChain(data, buf, &j, i, len);
		while (j < len)
		{
			if (the_chain(data, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (my_strlen(p));
	}

	*buf_p = buf;
	return (r); /* the length of the buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(data_t *data, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(data->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(data_t *data, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(data, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = my_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = my_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		my_strncat(new_p, buf + i, k - i);
	else
		my_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handle_sigint - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	my_putchar(BUF_FLUSH);
}
