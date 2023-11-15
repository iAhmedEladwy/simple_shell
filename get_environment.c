#include "shell.h"

/**
 * get_env - returns the string array copy of our environ
 * @info: structure containing potential arguments
 *
 * Return: 0
 */
char **get_env(info_t *info)
{
	if (!info->environ || info->env_change)
	{
		info->environ = list_to_str(info->env);
		info->env_change = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - remove an environment variable
 * @info: structure contain potential arguments
 * @var: string env var
 *
 * Return: 1 or 0
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = _startWith(node->data, var);
		if (ptr && *ptr == '=')
		{
			info->env_change = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_change);
}

/**
 * _setenv - initialize a new environment variables
 * @info: new struct
 * @var: the string env property
 * @value: the string env value
 *
 * Return: 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = 0;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;

	while (node)
	{
		ptr = _startWith(node->data, var);
		if (ptr && *ptr == '=')
		{
			free(node->data);
			node->data = buf;
			info->env_change = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_change = 1;
	return (0);
}
