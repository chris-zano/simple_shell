#include "shell.h"

/**
 * printlog - prints the strings in an array of strings
 *
 * @strarr: array of strings
 *
 * Return: void
 */

void printlog(char **strarr)
{
	int i = 0;

	for (i = 0; strarr[i]; i++)
		printf("log -> %s\n", strarr[i]);
}
