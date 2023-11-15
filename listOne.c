#include "shell.h"

/**
 * add_node - adds a new node at the beginning of a list_t list
 * @head: head of node
 * @str: the string to add as head
 * @num: node index
 *
 * Return: data
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *data;

	if (!head)
		return (NULL);

	data = malloc(sizeof(list_t));
	if (!data)
		return (NULL);
	_memoryset((void *)data, 0, sizeof(list_t));
	data->num = num;
	if (str)
	{
		data->data = _strdup(str);
		if (!data->data)
		{
			free(data);
			return (NULL);
		}
	}
	data->next = *head;
	*head = data;
	return (data);
}

/**
 * add_node_end - adds a new node at the end of a list_t list
 * @head: the pointer to struct
 * @str: the string to dup
 * @num: node index;
 *
 * Return: data
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *data, *current;

	if (!head)
		return (NULL);
	current = *head;
	data = malloc(sizeof(list_t));
	if (!data)
		return (NULL);
	_memoryset((void *)data, 0, sizeof(list_t));
	data->num = num;
	if (str)
	{
		data->data = _strdup(str);
		if (!data->data)
		{
			free(data);
			return (NULL);
		}
	}
	if (current)
	{
		while (current->next)
			current = current->next;
		current->next = data;
	}
	else
		*head = data;
	return (data);
}

/**
 * _pListstr - prints only str elements
 * @head: the head node
 *
 * Return: i
 */

size_t _pListstr(const list_t *head)
{
	size_t i;

	while (head)
	{
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
 * delete_node_at_index - function that deletes the node
 * at index of a list_t linked list.
 * @head: the head of struct
 * @index: the index
 *
 * Return: (1) on succeeded
 *					(-1) on failed
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *cur, *prev;
	unsigned int i = 0;

	if (!*head || !head)
		return (0);

	if (!index)
	{
		cur = *head;
		*head = (*head)->next;
		free(cur->data);
		free(cur);
		return (1);
	}
	cur = *head;
	while (cur)
	{
		if (i == index)
		{
			prev->next = cur->next;
			free(cur->data);
			free(cur);
			return (1);
		}
		i++;
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
