#include "shell.h"

/**
 * openhist_file - gets the history file
 * @data: parameter struct
 *
 * Return: allocated string containg history file
 */

char *openhist_file(unistruct_t *data)
{
	char *buf, *dir;

	dir = _getenv(data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE_LIST) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HISTORY_FILE_LIST);
	return (buf);
}

/**
 * write_to_hist - creates a file, or appends to an existing file
 * @data: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_to_hist(unistruct_t *data)
{
	ssize_t fd;
	char *filename = openhist_file(data);
	dash_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(CLEAR_BUFFER, fd);
	close(fd);
	return (1);
}

/**
 * fetch_hist - reads history from file
 * @data: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int fetch_hist(unistruct_t *data)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = openhist_file(data);

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
			append_hist_file(data, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		append_hist_file(data, buf + last, linecount++);
	free(buf);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_MAX)
		delete_node_at_index(&(data->history), 0);
	renumber_history(data);
	return (data->histcount);
}

/**
 * append_hist_file - adds to history
 * @data: Structure definition
 * @buf: buffer
 * @linecount: history count
 *
 * Return: Always 0
 */
int append_hist_file(unistruct_t *data, char *buf, int linecount)
{
	dash_t *node = NULL;

	if (data->history)
		node = data->history;
	add_node_end(&node, buf, linecount);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * renumber_history - set histry count++
 * @data: struct defintion
 * Return: histcount
 */
int renumber_history(unistruct_t *data)
{
	dash_t *node = data->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (data->histcount = i);
}
