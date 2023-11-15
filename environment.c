#include "shell.h"

/**
 * _env - print the current envirment
 * @info: the information
 *
 * Return: 0
 */

int _env(info_t *info)
{
	_pListstr(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an enviroment
 * @info: the new struct
 * @name: env var name
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = _startWith(node->data, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _thesetenv - inti a new environment variables | modify
 * @info: new struct
 *
 * Return: 0
 */
int _thesetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_errorPuts("Incorrect number of args\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * _theunsetenv - remove an environment variables
 * @info: new struct
 *
 * Return: 0
 */
int _theunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_errorPuts("few Args\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);
	return (0);
}
/**
 * _pop_env_list - populate env linked list
 * @info: new struct
 *
 * Return: 0
 */
int _pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
