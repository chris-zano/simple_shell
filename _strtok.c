#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100

char **_strtok(char *str)
{
	char **words = malloc(MAX_WORDS * sizeof(char *));
	int i = 0, len;
	char *p = str;
	char *q;

	if (words == NULL)
	{
		return (NULL);
	}

	while (*p != '\0' && i < MAX_WORDS)
	{
		/* Skip leading whitespace */
		while (*p != '\0' && isspace(*p))
		{
			p++;
		}

		/* Find end of word */
		q = p;
		while (*q != '\0' && !isspace(*q))
		{
			q++;
		}

		/* Allocate new string and copy word */
		len = q - p;
		if (len > 0)
		{
			words[i] = malloc(len + 1);
			if (words[i] == NULL)
			{
				/* Free previously allocated memory */
				for (int j = 0; j < i; j++)
				{
					free(words[j]);
				}
				free(words);
				return (NULL);
			}
			strncpy(words[i], p, len);
			words[i][len] = '\0';
			i++;
		}

		/* Move to next word */
		p = q;
	}
	words[i] = NULL;
	
	return (words);
}
