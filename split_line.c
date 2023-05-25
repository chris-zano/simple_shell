#include "shell.h"
#include "main.h"

/**
 * split_line - splits a line of strings into individual tokens of strings
 * @line: pointer to a string of text;
 * Return: An array containing the tokenized strings
 */

char **split_line(char *line)
{
	int buffsize = TK_BUFF_SIZE;
	int position = 0, i = 0;
	char **tokens = malloc(buffsize * sizeof(char *));
	char *token;

	for (i = 0; line[i] != '\0'; i++)
		if (line[i] == ';')
		{
			tokens[position] = NULL;
			return (tokens);
		}

	if (!tokens)
	{
		_printf("./hsh: %d: %s\n", errno, strerror(errno));
		free(tokens);
		exit(EXIT_FAILURE);
	}
	token = _strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= buffsize)
		{
			buffsize += TK_BUFF_SIZE;
			tokens = realloc(tokens, buffsize * sizeof(char *));
			if (!tokens)
			{
				_printf("./hsh: %d: %s\n", errno, strerror(errno));
				free(tokens);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;

	return (tokens);
}

/**
 * _split - splits a line separated by command separator ;
 *
 * @buffer: argument container commands split by ;
 *
 * Return: 0, Always
 */

int _split(char *buffer)
{
	char *buf_copy = _strdup(buffer);
	char **array, **args, *tok;
	char *builtin_args[] = {"exit", "setenv", "unsetenv", "cd", "alias", NULL};
	size_t len = 0, i = 0, j = 0;

	while (buffer[len])
	{
		len++;
	}
	array = malloc((len + 1) * sizeof(char *));

	if (array == NULL)
		return (-1);
	tok = _strtok(buf_copy, ";");

	while (tok != NULL)
	{
		array[i] = tok;
		tok = _strtok(NULL, ";");
		i++;
	}
	array[i] = NULL;

	while (j < i)
	{
		args = split_line(array[j]);
		search_execute(args, builtin_args);
		j++;
	}
	return (0);
}
