#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @data: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(unistruct_t *data, char **buf, size_t *len)
{
	ssize_t val = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		val = _getline(data, buf, &len_p);
		if (val > 0)
		{
			if ((*buf)[val - 1] == '\n')
			{
				(*buf)[val - 1] = '\0';
				val--;
			}
			data->lc_flag = 1;
		}
	}
	return (val);
}

/**
 * get_input - gets a line minus the newline
 * @data: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(unistruct_t *data)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t val = 0;
	char **buf_p = &(data->arg), *p;

	_putchar(CLEAR_BUFFER);
	val = input_buf(data, &buf, &len);
	if (val == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		cont_add(data, buf, &j, i, len);
		while (j < len)
		{
			if (dash_logic(data, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->cbuffer_type = RESET_DEF;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (val);
}

/**
 * read_buf - reads a buffer
 * @data: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: val
 */
ssize_t read_buf(unistruct_t *data, char *buf, size_t *i)
{
	ssize_t val = 0;

	if (*i)
		return (0);
	val = read(data->readfdes, buf, READ_BUF_SIZE);
	if (val >= 0)
		*i = val;
	return (val);
}

/**
 * _getline - gets the next line of input from STDIN
 * @data: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(unistruct_t *data, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t val = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	val = read_buf(data, buf, &len);
	if (val == -1 || (val == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = dash_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
