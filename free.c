#include "shell.h"

/**
 * freeall - frees shell session members
 * @session: last shell session
 */
void freeall(shell *session)
{
	if (session->env_list)
		freelist(session->env_list);
	if (session->aliases)
		freelist(session->aliases);
	if (session->args)
		freeargs(session->args);
}

/**
 * freeargbuffer - frees args and buffer
 * @session: input shell session
 */
void freeargbuffer(shell *session)
{
	freeargs(session->args);
	free(session->buffer);
}

/**
 * freelist - frees a linked list
 * @head: double pointer to head of list
 */
void freelist(list *head)
{
	list *current;
	list *tmp;

	if (!head)
		return;
	current = head;
	while (current)
	{
		tmp = current;
		current = tmp->next;
		free(tmp->string);
		free(tmp);
	}
	head = NULL;
}

/**
 * freeargs - helper func that frees double pointer arg
 * @args: array of char pointers
 */
void freeargs(char **args)
{
	int i = 0;

	while (args[i])
		free(args[i++]);
	free(args);
}
