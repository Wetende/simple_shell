#include "shell.h"

/**
 * is_command - function that determines whether a file is executable
 * @data: the data struct
 * @path: the path to target file
 *
 * Return: 1 if true, 0 if false
 */
int is_command(data_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - duplicates characters
 * @pstring: the PATH string
 * @start: the index to start from
 * @stop: the index to stop at
 *
 * Return: a pointer to new buffer
 */
char *duplicate_chars(char *pstring, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pstring[i] != ':')
			buf[k++] = pstring[i];
	buf[k] = 0;
	return (buf);
}

/**
 * search_path - finds given command in the PATH string
 * @data: the data struct
 * @pstring: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *search_path(data_t *info, char *pstring, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pstring)
		return (NULL);
	if ((my_strlen(cmd) > 2) && _beginWith(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pstring[i] || pstring[i] == ':')
		{
			path = duplicate_chars(pstring, curr_pos, i);
			if (!*path)
				my_strcat(path, cmd);
			else
			{
				my_strcat(path, "/");
				my_strcat(path, cmd);
			}
			if (is_command(info, path))
				return (path);
			if (!pstring[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
