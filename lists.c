#include "shell.h"
/**
 * addnode - adds a new node at the beginning of a linked list
 * @head: head of a linked list
 * @string: string to be added
 * Return: address to the new element
 */
list *addnode(list **head, char *string)
{
	list *node;

	if (string == NULL)
		return (NULL);
	node = malloc(sizeof(list));
	if (node == NULL)
	{
		perror("Malloc Failure\n");
		exit(errno);
	}

	node->string = duplicate(string);
	if (node->string == NULL)
	{
		perror("Malloc failed\n");
		exit(errno);
	}
	node->next = *head;
	*head = node;
	return (node);
}

/**
  *node_search_index - searches for a string in the list
  *@head: linked list
  *@string: string to be searched for
  *Return: index of node with the string
  */
int node_search_index(list *head, char *string)
{
	int index = 0;
	list *lists = head;
	char *ptr, *str;
	int i = 0, length, j;

	while (lists)
	{
		i = 0;
		ptr = char_locate('=', lists->string);
		length = ptr - lists->string;
		str = malloc(sizeof(char) * (length + 1));
		while (i < length)
		{
			str[i] = lists->string[i];
			i++;
		}
		str[i] = 0;
		j = compare(string, str);
		if (j == 0)
		{
			free(str);
			return (index);
		}
		index++;
		lists = lists->next;
		free(str);
	}
	return (-1);
}
/**
 * addendnode - adds a new node at the end of a linked list
 * @head: head
 * @string: string
 * Return: address of the new element
 */
list *addendnode(list **head, char *string)
{
	list *new, *temp;

	new = malloc(sizeof(list));
	if (new == NULL)
	{
		perror("Malloc Failure");
		exit(errno);
	}
	new->string = duplicate(string);
	if (new->string == NULL)
	{
		perror("Malloc Failure");
		exit(errno);
	}
	new->next = NULL;
	temp = *head;
	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

/**
 * listlength - returns the length of a linked list
 * @head: head of linked list
 * Return: length of list
 */

size_t listlength(list *head)
{
	size_t len = 0;
	list *temp = head;

	while (temp)
	{
		temp = temp->next;
		len++;
	}

	return (len);
}

/**
 * nodesprint - prints all the elements of a linked list
 * @head: singly linked list
 * Return: number of nodes
 */
int nodesprint(list *head)
{
	size_t num = 0;
	list *temp = head;

	while (temp)
	{
		write(STDOUT_FILENO, temp->string, length(temp->string));
		write(STDOUT_FILENO, "\n", 1);
		temp = temp->next;
		num++;
	}

	return (num);
}
