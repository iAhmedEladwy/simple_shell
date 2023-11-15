#include "shell.h"

/**
 * _history - display the history list
 * @info: struct
 *
 * Return: 0
 */
int _history(info_t *info)
{
	_printList(info->history);
	return (0);
}

/**
 * _unsetalias - unset alias to string
 * @info: struct
 * @str: the string alias
 *
 * Return: 0 or 1
 */
int _unsetalias(info_t *info, char *str)
{
	char *ptr, c;
	int ret;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	ret = delete_node_at_index(&(info->alias),
										get_n_index(info->alias, node_startwith(info->alias, str, -1)));
	*ptr = c;
	return (ret);
}

/**
 * _setalias - sets alias to string
 * @info: struct
 * @str: the string
 *
 * Return: 0 or 1
 */
int _setalias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);

	if (!*++ptr)
		return (_unsetalias(info, str));

	_unsetalias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _printalias - print an alias string
 * @node: the alias node
 *
 * Return: 0 or 1
 */
int _printalias(list_t *node)
{
	char *str = NULL, *ptr = NULL;

	if (node)
	{
		str = _strchr(node->data, '=');
		for (ptr = node->data; ptr <= str; ptr++)
			_putchar(*ptr);
		_putchar('\'');
		_puts(str + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - the alias builtin
 * @info: struct
 *
 * Return: 0
 */
int _alias(info_t *info)
{
	int i = 0;
	char *str = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		str = _strchr(info->argv[i], '=');
		if (str)
			_setalias(info, info->argv[i]);
		else
			_printalias(node_startwith(info->alias, info->argv[i], '='));
	}
	return (0);
}
