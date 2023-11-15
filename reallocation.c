#include "shell.h"

/**
 * _memoryset - fills memory with a constant byte
 * @s: pointer to the memory
 * @b: the byte
 * @n: the amount of bytes
 *
 * Return: pointer to the memory
 */
char *_memoryset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * _free - free a string of string
 * @pp: string of string
 *
 * Return: nothing
 */
void _free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);

	free(a);
}

/**
 * _reallocat - reallocates block of memory
 * @ptr: pointer to previous mallocated block
 * @old_size: size of old block
 * @new_size: size of new block
 *
 * Return: pointer
 */
void *_reallocat(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
