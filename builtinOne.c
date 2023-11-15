#include "shell.h"

/**
 * _exit_ - function that exit the shell
 * @info: structure
 *
 * Return: given exit status
 */
int _exit_(info_t *info)
{
	int checkexit;

	if (info->argv[1])
	{
		checkexit = _err_atoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			_printError(info, "Illegal number: ");
			_errorPuts(info->argv[1]);
			_errorPutchar('\n');
			return (1);
		}
		info->e_num = _err_atoi(info->argv[1]);
		return (-2);
	}
	info->e_num = -1;
	return (-2);
}

/**
 * _cd - changes the current directory
 * @info: struct
 *
 * Return: 0
 */
int _cd(info_t *info)
{
	char *str, *dir, buf[1024];
	int change_dir;

	str = getcwd(buf, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			change_dir =
					chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			change_dir = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		change_dir =
				chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		change_dir = chdir(info->argv[1]);
	if (change_dir == -1)
	{
		_printError(info, "can't cd to ");
		_errorPuts(info->argv[1]), _errorPutchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _help - show all about command
 * @info: struct
 *
 * Return: 0
 */
int _help(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
