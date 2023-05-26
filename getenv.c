#include "shell.h"

/**
 * get_environ - returns copy of our environ
 *
 * @data: Structure def.
 *
 * Return: Always 0
 */
char **get_environ(unistruct_t *data)
{
	if (!data->environ || data->isenv_on)
	{
		data->environ = dash_to_strings(data->env);
		data->isenv_on = 0;
	}

	return (data->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @data: Structure def
 * @var: the string env var property
 *  Return: 0 (success), 1 (fail)
 */
int _unsetenv(unistruct_t *data, char *var)
{
	dash_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = comp_ndle(node->str, var);
		if (p && *p == '=')
		{
			data->isenv_on = delete_node_at_index(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->isenv_on);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(unistruct_t *data, char *var, char *value)
{
	char *buf = NULL;
	dash_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = data->env;
	while (node)
	{
		p = comp_ndle(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			data->isenv_on = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(data->env), buf, 0);
	free(buf);
	data->isenv_on = 1;
	return (0);
}
