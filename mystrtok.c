#include "main.h"

char *mystrtok(char *str, const char *delim)
{
	static char *last;
	char *tok;

	if (str == NULL && last == NULL)
	{
		return (NULL);
	}
    
	if (str != NULL)
	{
		last = str;
	}

	tok = last;

	while (*last != '\0')
	{
		const char *d = delim;
		while (*d != '\0')
		{
			if (*last == *d)
			{
				*last = '\0';
				last++;
				if (tok != last)
				{
					return (tok);
				}
				else
				{
					tok = last;
					break;
				}
			}
			d++;
		}
		last++;
	}

	if (tok == last)
	{
		return (NULL);
	}
	else
	{
		return (tok);
	}
}
