#include "shell.h"

/**
 * hsh - main shell
 * @info: structure
 * @av: the argument vector
 *
 * Return: 0 or 1
 */
int hsh(info_t *info, char **av)
{
	ssize_t read_byte = 0;
	int result = 0;

	while (read_byte != -1 && result != -2)
	{
		clearInfo(info);
		if (_isInteractive(info))
			_puts("#cisfun$ ");
		_errorPutchar(BUFF_FLUSH);
		read_byte = get_input(info);
		if (read_byte != -1)
		{
			setInfo(info, av);
			result = findBuiltin(info);
			if (result == -1)
				findCMD(info);
		}
		else if (_isInteractive(info))
			_putchar('\n');
		freeInfo(info, 0);
	}
	_writeHistory(info);
	freeInfo(info, 1);
	if (!_isInteractive(info) && info->status)
		exit(info->status);
	if (result == -2)
	{
		if (info->e_num == -1)
			exit(info->status);
		exit(info->e_num);
	}
	return (result);
}

/**
 * findBuiltin - finds builtin command
 * @info: struct
 *
 * Return: -1 or 0 or 1 or -2
 */
int findBuiltin(info_t *info)
{
	int i, result = -1;
	built_table builtin_table[] = {
			{"exit", _exit_},
			{"env", _env},
			{"help", _help},
			{"history", _history},
			{"setenv", _thesetenv},
			{"unsetenv", _theunsetenv},
			{"cd", _cd},
			{"alias", _alias},
			{NULL, NULL}
	};

	for (i = 0; builtin_table[i].type; i++)
		if (_strcmp(info->argv[0], builtin_table[i].type) == 0)
		{
			info->l_count++;
			result = builtin_table[i].func(info);
			break;
		}
	return (result);
}

/**
 * findCMD - find command in path
 * @info: struct
 *
 * Return: nothing
 */

void findCMD(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->l_count_flag == 1)
	{
		info->l_count++;
		info->l_count_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!_isdelim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkCMD(info);
	}
	else
	{
		if ((_isInteractive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && isCMD(info, info->argv[0]))
			forkCMD(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_printError(info, "not found\n");
		}
	}
}

/**
 * forkCMD - forks an exec thread to run command
 * @info: struct
 *
 * Return: nothing
 */
void forkCMD(info_t *info)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(info->path, info->argv, get_env(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_printError(info, "Permission denied\n");
		}
	}
}
