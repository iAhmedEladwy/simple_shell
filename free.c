#include "shell.h"

/**
 * free_p - free pointer
 * @p: address of pointer to free
 *
 * Return: 1 or 0
 */
int free_p(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

/**
 * free_l - free all nodes of a list
 * @head_P: address of pointer to head node
 *
 * Return: nothing
 */
void free_l(list_t **head_P)
{
	list_t *cur, *next_cur, *h;

	if (!head_P || !*head_P)
		return;

	h = *head_P;
	cur = h;
	while (cur)
	{
		next_cur = cur->next;
		free(cur->data);
		free(cur);
		cur = next_cur;
	}
	*head_P = NULL;
}
