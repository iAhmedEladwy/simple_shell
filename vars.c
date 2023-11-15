#include "shell.h"

/**
 * _isChain - test if current char in buffre is a chain delimeter
 * @info: struct
 * @buf: char buffer
 * @str: address of current possition iin buf
 *
 * Return: 1 or 0
 */
int _isChain(info_t *info, char *buf, size_t *str)
{
	size_t i = *str;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';')
	{
		buf[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*str = i;
	return (1);
}

/**
 * _checkChain - check of contenue chaining base on last status
 * @info: struct
 * @buf: char buffer
 * @str: address of current position in buf
 * @i: stast position
 * @length: lrngth of buffer
 *
 * Return: nothing
 */
void _checkChain(info_t *info, char *buf, size_t *str, size_t i, size_t length)
{
	size_t j = *str;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = length;
		}
	}
	*str = j;
}

/**
 * _aliasReplac - replaces an aliases
 * @info: struct
 *
 * Return: 1 or 0
 */
int _aliasReplac(info_t *info)
{
	int i;
	list_t *node;
	char *str;

	for (i = 0; i < 10; i++)
	{
		node = node_startwith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		str = _strchr(node->data, '=');
		if (!str)
			return (0);
		str = _strdup(str + 1);
		if (!str)
			return (0);
		info->argv[0] = str;
	}
	return (1);
}

/**
 * _varsReplac - replaces vars in the string
 * @info: struct
 *
 * Return: 1 or 0
 */
int _varsReplac(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			_stringReplac(&(info->argv[i]),
				_strdup(conv_num(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			_stringReplac(&(info->argv[i]),
				_strdup(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = node_startwith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			_stringReplac(&(info->argv[i]),
										_strdup(_strchr(node->data, '=') + 1));
			continue;
		}

		_stringReplac(&info->argv[i], _strdup(""));
	}

	return (0);
}

/**
 * _stringReplac - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 or 0
 */
int _stringReplac(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
