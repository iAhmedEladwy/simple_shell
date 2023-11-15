#include "shell.h"

/**
 * isCMD - check if file is an excutable
 * @info: info struct
 * @path: Path to file
 *
 * Return: 1 => true | 0 => otherwise
 */

int isCMD(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * _isalpha - checks alphabetic
 * @c: input char
 *
 * Return: 1 if c is char | 0 => otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _isdelim - check c is a delimeter or not
 * @c: char to check
 * @delim: delimeter string
 *
 * Return: 1 => true | 0 => false
 */

int _isdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isInteractive - check if shell is in interactive mode or not
 * @info: struct address
 *
 * Return: 1 => interactive mode | 0 oterwise
 */
int _isInteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
