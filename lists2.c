#include "shell.h"

/**
  *create_list - creates a linked list of environmental variables
  *@env: array of env strings
  *Return: pointer to the list
  */
list *create_list(char **env)
{
	list *head = NULL;
	int i = 0;

	while (env[i])
	{
		addendnode(&head, env[i]);
		i++;
	}
	return (head);
}

/**
 * nodeatindex - inserts a new node at a given position
 * @head: pointer to linked list
 * @index: index
 * @string: new string to be added
 * Return: address of the new node
 */
list *nodeatindex(list **head, int index, char *string)
{
	int i;
	list *ptr, *temp = *head;

	ptr = malloc(sizeof(list));
	if (!ptr || !head)
	{
		if (!ptr)
			perror("Malloc failure");
		exit(errno);
	}

	ptr->string = duplicate(string);
	if (ptr->string == NULL)
	{
		perror("Malloc failure");
		exit(errno);
	}
	if (index == 0)
	{
		ptr->next = *head;
		*head = ptr;
		return (ptr);
	}

	for (i = 0; i < index && temp; i++)
	{
		if (i == index - 1)
		{
			ptr->next = temp->next;
			temp->next = ptr;
			return (ptr);
		}
		temp = temp->next;
	}

	return (NULL);
}

/**
 * delete_node - deletes a node at a particular index
 * @head: pointer to singly linked list
 * @index: index
 * Return: 1 (success) -1(failure)
 */
int delete_node(list **head, int index)
{
	int i;
	list *temp = *head, *present = NULL;

	if (*head == NULL)
		return (-1);

	if (index == 0)
	{
		free(temp->string);
		*head = (*head)->next;
		free(temp);
		return (1);
	}

	for (i = 0; i < index - 1; i++)
	{
		if (!temp || !(temp->next))
			return (-1);
		temp = temp->next;
	}
	present = temp->next;
	temp->next = present->next;
	free(present->string);
	free(present);
	return (1);
}
/**
 * getNodeAtIndex - returns the nth node of a listint_t linked list
 * @head: pointer to head of list
 * @index: index of value to be returned
 * Return: address of node at input index
 */
char *getNodeAtIndex(list *head, int index)
{
	int count = 0;
	list *current;
	char *ptr;

	current = head;
	while (current)
	{
		if (count == index)
		{
			ptr = duplicate(current->string);
			return (ptr);
		}
		count++;
		current = current->next;
	}
	return (NULL);
}
