#include "shell.h"

/**
 * clearInfo - clear info_t
 * @info: struct address
 *
 * Return: void
 */
void clearInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfo - init info_t struct
 * @info: struct address
 * @av: argv
 *
 * Return: void
 */

void setInfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = _strtok(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		_aliasReplac(info);
		_varsReplac(info);
	}
}
/**
 * freeInfo - free info struct fields
 * @info: struct
 * @all: true if freeing all fields
 *
 * Return: void
 */
void freeInfo(info_t *info, int all)
{
	_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_l(&(info->env));
		if (info->history)
			free_l(&(info->history));
		if (info->alias)
			free_l(&(info->alias));
		_free(info->environ);
		info->environ = NULL;
		free_p((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFF_FLUSH);
	}
}
