#include "shell.h"

/**
 * _dupchar - duplicates char
 * @strpath: string path
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buf
 */
char *_dupchar(char *strpath, int start, int stop)
{
	static char buf[1024];
	int i, j;

	for (j = 0, i = start; i < stop; i++)
		if (strpath[i] != ':')
			buf[j++] = strpath[i];
	buf[j] = 0;
	return (buf);
}
/**
 * find_path - finds this cmd in the PATH
 * @info: struct info
 * @strpath: string PATH
 * @cmd: cmd to find
 *
 * Return: if exist => full path | NULL
 */
char *find_path(info_t *info, char *strpath, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!strpath)
		return (NULL);
	if ((_strlen(cmd) > 2) && _startWith(cmd, "./"))
		if (isCMD(info, cmd))
			return (cmd);
	while (1)
	{
		if (!strpath[i] || strpath[i] == ':')
		{
			path = _dupchar(strpath, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (isCMD(info, path))
				return (path);
			if (!strpath[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
