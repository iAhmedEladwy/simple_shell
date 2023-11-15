#include "shell.h"

/**
 * _strdup - make duplcation to string
 * @src: the string to make duplcation
 *
 * Return: str
 */

char *_strdup(const char *src)
{
	char *str;
	int len = 0;

	if (!src)
		return (NULL);
	while (*src++)
		len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	for (len++; len--;)
		str[len] = *--src;
	return (str);
}

/**
 * *_strcat - function that concatenates two strings
 * @dest: string one
 * @src: string two
 *
 * Return: ptr
 */

char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ptr);
}

/**
 * _strlen - fucntion that return string length
 * @str: the string
 *
 * Return: i
 */

int _strlen(char *str)
{
	int len = 0;

	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

/**
 * _strcmp - function that compare two string
 * @strOne: String One
 * @strTwo: String Two
 *
 * Return: 0
 */
int _strcmp(char *strOne, char *strTwo)
{
	while (*strOne && *strTwo)
	{
		if (*strOne != *strTwo)
			return (*strOne - *strTwo);
		strOne++;
		strTwo++;
	}
	if (*strOne == *strTwo)
		return (0);
	else
		return (*strOne < *strTwo ? (-1) : (1));
}
/**
 * _strchr - locates char in a string
 * @str: stirng to be parsed
 * @c: character
 *
 * Return: pointer to
 */
char *_strchr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}
