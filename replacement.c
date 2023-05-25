#include "shell.h"

/**
 * dash_logic - is character sequence a chain delimeter
 * @data: struct
 * @buf: buffer
 * @p: address
 * Return: 1 , 0 always
 */
int dash_logic(unistruct_t *data, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data->cbuffer_type = SET_CON;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data->cbuffer_type = SET_LOG;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		data->cbuffer_type = SET_COM;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * interactive_mode - checks if interactive mode is true
 * @data: struct address
 * Return: 1 (true), 0(false)
 */
int interactive_mode(unistruct_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfdes <= 2);
}

/**
 * dash_setalias - replaces an aliases in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int dash_setalias(unistruct_t *data)
{
	int i;
	dash_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_comp_ndle(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
