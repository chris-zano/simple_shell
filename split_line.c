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
	char **tokens = malloc(buffsize * sizeof(char *));
	char **retcal, *token;

	for (i = 0; line[i] != '\0'; i++)
		if (line[i] == ';')
		{
			tokens[position] = NULL;
			return (tokens);
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
