#include "shell.h"

/**
 * reset_unistruct - initializes unistruct_t struct
 * @data: struct address
 */
void reset_unistruct(unistruct_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * init_unistruct - initializes unistruct_t struct
 * @data: struct address
 * @av: argument vector
 * Return: void
 */
void init_unistruct(unistruct_t *data, char **av)
{
	int i = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = split_line(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;
		dash_setalias(data);
		var_replcmnt(data);
	}
}

/**
 * free_data - frees unistruct_t struct fields
 * @data: struct address
 * @all: true
 * Return: void
 */
void free_data(unistruct_t *data, int all)
{
	dash_ffree(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->arg_buffer)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		dash_ffree(data->environ);
			data->environ = NULL;
		dash_free((void **)data->arg_buffer);
		if (data->readfdes > 2)
			close(data->readfdes);
		_putchar(CLEAR_BUFFER);
	}
}

/**
 * dash_free - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int dash_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
