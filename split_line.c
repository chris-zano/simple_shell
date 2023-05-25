#include "shell.h"

/**
 * **split_line - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **split_line(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_checkdelim(str[i], d) && (_checkdelim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (_checkdelim(str[i], d))
			i++;
		k = 0;
		while (!_checkdelim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
/**
 * var_replcmnt - replaces vars in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int var_replcmnt(unistruct_t *data)
{
	int i = 0;
	dash_t *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;

		if (!_strcmp(data->argv[i], "$?"))
		{
			replace_string(&(data->argv[i]),
				_strdup(convert_number(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->argv[i], "$$"))
		{
			replace_string(&(data->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_comp_ndle(data->env, &data->argv[i][1], '=');
		if (node)
		{
			replace_string(&(data->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&data->argv[i], _strdup(""));

	}
	return (0);
}


/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * dash_ffree - frees an array of strings
 * @pp: pointer to array of stings
 */
void dash_ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * dash_realloc - reallocates a block of memory
 * @ptr: ptr to prev block
 * @ol_s: previous block
 * @nw_s: new block
 *
 * Return: pointer to address
 */
void *dash_realloc(void *ptr, unsigned int ol_s, unsigned int nw_s)
{
	char *p;

	if (!ptr)
		return (malloc(nw_s));
	if (!nw_s)
		return (free(ptr), NULL);
	if (nw_s == ol_s)
		return (ptr);

	p = malloc(nw_s);
	if (!p)
		return (NULL);

	ol_s = ol_s < nw_s ? ol_s : nw_s;
	while (ol_s--)
		p[ol_s] = ((char *)ptr)[ol_s];
	free(ptr);
	return (p);
}
