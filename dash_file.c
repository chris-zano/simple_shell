#include "shell.h"

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *hist_str, *name = "";
	int len, hist = 0;

	hist_str = dash_toalpha(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * proc_file_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last dash_executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0, old_size = 120;
	char *line, buffer[120];
	int rec;

	file = open(file_path, O_RDONLY);
	if (file == -1)
		return (127);
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (127);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = dash_realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	rec = filecommands(line, line_size, exe_ret);
	return (rec);
}

/**
 * filecommands - completes the proc_file_command
 * breaking excess code into two separate functions
 * @line: see proc_file_command
 * @line_size: see proc_file_command
 * @ret: see proc_file_command
 *
 * Return: rec to proc_file_command
*/

int filecommands(char *line, unsigned int line_size, int *ret)
{
	ssize_t i;
	int *exe_ret, val, rec;
	char **args, **front;

	val = 127;
	exe_ret = &val;
	*exe_ret = 127;
	dash_replace(&line, ret);
	dash_logic(&line, line_size);
	args = dash_strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (_ops_in_args(args) != 0)
	{
		dash_freeargs(args, args);
		return (127);
	}
	front = args;
	for (i = 0; args[i]; i++)
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			rec = _partargs(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	rec = _partargs(args, front, exe_ret);
	free(front);
	return (rec);
}
