#include "shell.h"

/**
 * _errorPuts - prints an input string
 * @str: string to be printed
 *
 * Return: nothing
 */
void _errorPuts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_errorPutchar(str[i]);
		i++;
	}
}


/**
 * _errorPutchar -write character to stderr
 * @c: character to be printed
 *
 * Return: 1 or -1
 */
int _errorPutchar(char c)
{
	static int i;
	static char buffer[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buffer[i++] = c;
	return (1);
}
/**
 * _putcharfd - write character to fd
 * @c: character to be printed
 * @fd: filedescriptor
 *
 * Return: 1 or -1
 */
int _putcharfd(char c, int fd)
{
	static int i;
	static char buffer[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: string to be printed
 * @fd: filedescriptor
 *
 * Return: numper of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i = i + _putcharfd(*str++, fd);
	}
	return (i);
}
