#include "shell.h"

/**
 * main - entry point
 *
 * @argc: arg count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	int o = (FILE_D_OPEN - 2) + (FILE_D_OPEN - 3);
	int set = 2;
	unistruct_t data[] = { INIT_LIST };

	if (argc == set)
	{
		o = open(argv[1], O_RDONLY);
		if (o == -1)
		{
			if (errno == ENOENT)
			{
				while (set == 2)
				{
					print_errorstr(argv[0]);
					print_errorstr(": 0: Can't open ");
					print_errorstr(argv[1]);
					set = 0;
				}
				write_errc('\n');
				write_errc(CLEAR_BUFFER);
				exit(EXIT_ENO_ENT);
			}
			}
			if(errno == EACCES)
				exit(EXIT_E_ACCES);
			return (EXIT_FAILURE);
		}
		data->readfdes = fd;
	}
	loadenviron_list(data);
	dash_loop(data, argv);
	return (EXIT_SUCCESS);
}

/**
 * dash_loop - main shell loop
 * @data: the parameter & return data struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int dash_loop(unistruct_t *data, char **av)
{
	ssize_t r = 0;
	int ret_val = 0;

	while (r != -1 && ret_val != -2)
	{
		reset_unistruct(data);
		if (interactive_mode(data))
			_puts("$ ");
		write_errc(CLEAR_BUFFER);
		r = get_input(data);
		if (r != -1)
		{
			init_unistruct(data, av);
			ret_val = is_builtin(data);
			if (ret_val == -1)
				search_command(data);
		}
		else if (interactive_mode(data))
			_putchar('\n');
		free_data(data, 0);
	}
	write_to_hist(data);
	free_data(data, 1);
	if (!interactive_mode(data) && data->status)
		exit(data->status);
	if (ret_val == -2)
	{
		if (data->error_coden == -1)
			exit(data->status);
		exit(data->error_coden);
	}
	return (ret_val);
}

/**
 * is_builtin - finds a builtin command
 * @data: parameter and structure
 * Return: -1 (fail), 0 (success)
 */
int is_builtin(unistruct_t *data)
{
	int i, ret_val = -1;
	builtint_t array[] = {
		{"exit", dash_exit},
		{"env", dash_env},
		{"setenv", dash_setenv},
		{"unsetenv", dash_unsetenv},
		{"cd", dash_cd},
		{NULL, NULL}
	};

	for (i = 0; array[i].type; i++)
		if (_strcmp(data->argv[0], array[i].type) == 0)
		{
			data->line_count++;
			ret_val = array[i].func(data);
			break;
		}
	return (ret_val);
}

/**
 * search_command - finds a command in PATH
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void search_command(unistruct_t *data)
{
	char *path = NULL;
	int i, j;

	data->path = data->argv[0];
	if (data->lc_flag == 1)
	{
		data->line_count++;
		data->lc_flag = 0;
	}
	for (i = 0, j = 0; data->arg[i]; i++)
		if (!_checkdelim(data->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = search_path(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		new_fork(data);
	}
	else
	{
		if ((interactive_mode(data) || _getenv(data, "PATH=")
			|| data->argv[0][0] == '/') && dash_is_cmd(data, data->argv[0]))
			new_fork(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * new_fork - forks a an exec thread to run cmd
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void new_fork(unistruct_t *data)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		_puts("Error: Failed to fork new process");
		return;
	}
	if (pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}
