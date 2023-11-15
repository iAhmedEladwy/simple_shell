#include "shell.h"

/**
 * _getHistory - gets history file
 * @info: struct
 *
 * Return: string containing history file
 */
char *_getHistory(info_t *info)
{
	char *buff, *ptr;

	ptr = _getenv(info, "HOME=");
	if (!ptr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(ptr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, ptr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * _writeHistory - creates a file
 * @info: struct
 *
 * Return: 1 or -1
 */
int _writeHistory(info_t *info)
{
	ssize_t fd;
	char *fName = _getHistory(info);
	list_t *node;

	if (!fName)
		return (-1);

	fd = open(fName, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fName);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->data, fd);
		_putcharfd('\n', fd);
	}
	_putcharfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _readHistory - reads history from file
 * @info: struct
 *
 * Return: 0 or history count
 */
int _readHistory(info_t *info)
{
	int i, last = 0, lCount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *fName = _getHistory(info);

	if (!fName)
		return (0);

	fd = open(fName, O_RDONLY);
	free(fName);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			_listHistory(info, buff + last, lCount++);
			last = i + 1;
		}
	if (last != i)
		_listHistory(info, buff + last, lCount++);
	free(buff);
	info->history_count = lCount;
	while (info->history_count-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	_renumberHistory(info);
	return (info->history_count);
}

/**
 * _listHistory - add entry to history list
 * @info: struct
 * @buff: bufffer
 * @lcount: history line count
 *
 * Return: 0
 */
int _listHistory(info_t *info, char *buff, int lcount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buff, lcount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * _renumberHistory - renumber histiry linked list
 * @info: struct
 *
 * Return: new history count
 */
int _renumberHistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->history_count = i);
}
