#include "shell.h"

/**
 * dfree - frees a double pointer to a string
 *
 * @dptr: a double pointer to strings
 *
 * Return: void
 */

void dfree(char **dptr)
{
	int i = 0;

	while (dptr[i] != NULL)
	{
		free(dptr[i]);
		i++;
	}

	free(dptr);
}

