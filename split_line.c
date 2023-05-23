#include "shell.h"

/**
 * split_line - splits a line of strings into individual tokens of strings
 * @line: pointer to a string of text;
 * Return: An array containing the tokenized strings
 */

char **split_line(char *line)
{
	int buffsize = TK_BUFF_SIZE;
	int position = 0, i = 0, j = 0;
	int retcal;
	char **tokens = malloc(buffsize * sizeof(char *));
	char *token;

	for (i = 0; line[i] != '\0'; i++)
		if (line[i] == ';')
		{
			retcal = _split(line);
			if (retcal == 0)
			{
				tokens[position] = NULL;
				return (tokens);
			}
			if (retcal != 0)
			{
				perror("failed to handle command separators");
				tokens[position] = NULL;
				return (tokens);
			}
		}

	if (!tokens)
	{
		perror("dash:Error");
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
				perror("dash:Error");
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;

	return (tokens);
}

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
		if (args != NULL)
		{
			search_execute(args, builtin_args);
			free(args);
		}
		j++;
	}
	return (0);
}
