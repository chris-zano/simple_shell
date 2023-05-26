#include "shell.h"

/**
 * search_path - finds this cmd in the PATH string
 *
 * @data: the data struct
 * @pathv: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *search_path(unistruct_t *data, char *pathv, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathv)
		return (NULL);
	if ((_strlen(cmd) > 2) && comp_ndle(cmd, "./"))
	{
		if (dash_is_cmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathv[i] || pathv[i] == ':')
		{
			path = duplicat_c(pathv, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (dash_is_cmd(data, path))
				return (path);
			if (!pathv[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * dash_exit - exits the shell
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if data.argv[0] != "exit"
 */
int dash_exit(unistruct_t *data)
{
	int val;

	if (data->argv[1])  /* If there is an exit arguement */
	{
		val = convert_atoi(data->argv[1]);
		if (val == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			print_errorstr(data->argv[1]);
			write_errc('\n');
			return (1);
		}
		data->error_coden = convert_atoi(data->argv[1]);
		return (-2);
	}
	data->error_coden = -1;
	return (-2);
}

/**
 * dash_cd - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int dash_cd(unistruct_t *data)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("Failed to get cwd\n");
	if (!data->argv[1])
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(data, "can't cd to ");
		print_errorstr(data->argv[1]), write_errc('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: void
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * comp_ndle - does h start with n
 * @h: val to search
 * @n: tsubstring
 * Return: NULL
 */
char *comp_ndle(const char *h, const char *n)
{
	while (*n)
		if (*n++ != *h++)
			return (NULL);
	return ((char *)h);
}
