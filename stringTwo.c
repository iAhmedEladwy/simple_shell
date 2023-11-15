#include "shell.h"

/**
 * _startWith - function that locates a substring
 * @haystack: string to search through
 * @needle: string to search for
 *
 * Return: null
 */
char *_startWith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _putchar - write charachter to stdout
 * @ch: charachter
 *
 * Return: 1 or -1
 */
int _putchar(char ch)
{
	static int i;
	static char buff[WRITE_BUFF_SIZE];

	if (ch == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (ch != BUFF_FLUSH)
		buff[i++] = ch;
	return (1);
}

/**
 * _puts - print string
 * @src: the string to be printed
 *
 * Return: nothing
 */
void _puts(char *src)
{
	int i = 0;

	if (!src)
		return;
	while (src[i] != '\0')
	{
		_putchar(src[i]);
		i++;
	}
}

/**
 * _strcpy - copies a string
 * @dest: destination
 * @src: source
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
