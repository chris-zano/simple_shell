#include "shell.h"

/**
 * convert_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0
 */
int convert_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @data: the parameter & return data struct
 * @estr: string containing specified error type
 * Return: 0 , -1
 */
void print_error(unistruct_t *data, char *estr)
{
	print_errorstr(data->fname);
	print_errorstr(": ");
	print_d(data->line_count, STDERR_FILENO);
	print_errorstr(": ");
	print_errorstr(data->argv[0]);
	print_errorstr(": ");
	print_errorstr(estr);
}

/**
 * print_d - function prints a decimal (integer) number (b 10)
 * @input: the input
 * @fd: the file to write to
 *
 * Return: count
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = write_errc;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converts a number
 * @x: input number
 * @b: the b
 * @flags: flags
 * Return: string type for the number
 */
char *convert_number(long int x, int b, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = x;

	if (!(flags & RESET_NON_NEG) && x < 0)
	{
		n = -x;
		sign = '-';

	}
	array = flags & RESET_CHAR_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * dash_is_cmd - determines if a file is an executable command
 * @data: the data struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int dash_is_cmd(unistruct_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
