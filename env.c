#include "shell.h"

/**
 * dash_env - prints the current environment
 *
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int dash_env(unistruct_t *data)
{
	print_list_str(data->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @data: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(unistruct_t *data, const char *name)
{
	dash_t *node = data->env;
	char *p;

	while (node)
	{
		p = comp_ndle(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * dash_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int dash_setenv(unistruct_t *data)
{
	if (data->argc != 3)
	{
		print_errorstr("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * dash_unsetenv - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int dash_unsetenv(unistruct_t *data)
{
	int i;

	if (data->argc == 1)
	{
		print_errorstr("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		_unsetenv(data, data->argv[i]);

	return (0);
}

/**
 * loadenviron_list - populates env linked list
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int loadenviron_list(unistruct_t *data)
{
	dash_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	data->env = node;
	return (0);
}
