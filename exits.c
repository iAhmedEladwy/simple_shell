#include "shell.h"

/**
 * strn_cpy - copies string
 * @dest: destination string
 * @src: source string
 * @n: number of character
 *
 * Return: concatenared string
 */
char *strn_cpy(char *dest, char *src, int n)
{
	int i, j;
	char *str = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 * strn_cat - concatenates two string
 * @dest: first string
 * @src: second string
 * @n: number of bytes
 *
 * Return: concatenated sring
 */
char *strn_cat(char *dest, char *src, int n)
{
	int i, j;
	char *str = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (str);
}
