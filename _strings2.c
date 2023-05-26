#include "shell.h"

/**
 **_strncat - concatenates two strings from args
 *
 * @dest: the first string
 * @src: the second string
 * @n: bytes
 *
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) pointer
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
dash_t *add_node(dash_t **head, const char *str, int num)
{
	dash_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(dash_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(dash_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}


/**
 **_strncpy - copies a string
 *@dest: the dest str
 *@src: the src str
 *@n: the count
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * duplicat_c - duplicates characters
 * @pathv: PATH
 * @start: start
 * @stop: stop
 *
 * Return: pointer to new buffer
 */
char *duplicat_c(char *pathv, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathv[i] != ':')
			buf[k++] = pathv[i];
	buf[k] = 0;
	return (buf);
}
