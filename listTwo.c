#include "shell.h"

/**
 * l_len - length of linked list
 * @head: liked list head
 *
 * Return: i
 */

size_t l_len(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * list_to_str - array of strings of the list->data
 * @head: list_t head
 *
 * Return: strings
 */
char **list_to_str(list_t *head)
{
	list_t *node = head;
	size_t i = l_len(head), j;
	char **strings;
	char *str;

	if (!head || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->data) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}
		str = _strcpy(str, node->data);
		strings[i] = str;
	}
	strings[i] = 0;
	return (strings);
}

/**
 * _printList - prints all elements of list_t
 * @head: list_t head
 *
 * Return: i
 */
size_t _printList(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(conv_num(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		if (head->data)
			_puts(head->data);
		else
			_puts("(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * node_startwith - node whose string starts with prefix
 * @node: pointer to list
 * @pre:string to match
 * @c: the next char
 *
 * Return: match node or NULL
 */
list_t *node_startwith(list_t *node, char *pre, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = _startWith(node->data, pre);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_n_index - gets the index of a node
 * @head: list_t head
 * @ptr_node: pointer to node
 *
 * Return: index of node or -1
 */
ssize_t get_n_index(list_t *head, list_t *ptr_node)
{
	size_t i = 0;

	while (head)
	{
		if (head == ptr_node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
