#include "shell.h"

/**
  *setenvFunc - sets a new value for an env variable
  *@session: shell info
  *Return: 1 on success and -1 on failure
  */
int setenvFunc(shell *session)
{
	int count = 0, index, len;
	static char buffer[BUFF_MAX];

	while (session->args[count])
		count++;
	setnull(buffer, 0);
	if (count != 3)
	{
		errno = EWSIZE;
		errorHandler(session);
		return (-1);
	}
	if (!(_isalpha(session->args[1][0])))
	{
		errno = ENOSTRING;
		errorHandler(session);
		return (-1);
	}
	len = length(session->args[1]) + length(session->args[2]) + 2;
	catenate(buffer, session->args[1]);
	catenate(buffer, "=");
	catenate(buffer, session->args[2]);
	setnull(buffer, (len - 1));
	index = node_search_index(session->env_list, session->args[1]);
	if (index < 0)
	{
		addendnode(&session->env_list, buffer);
		setnull(buffer, 0);
		return (1);
	}
	delete_node(&session->env_list, index);
	nodeatindex(&session->env_list, index, buffer);
	setnull(buffer, 0);
	return (1);
}

/**
 * unsetenvFunc - deletes env variable if exists;
 * will only accept valid variables names
 * @session: shell info
 * Return: Always 1 on success, -1 on failure
 */
int unsetenvFunc(shell *session)
{
	int foundVar, i = 1;
	list *head = session->env_list;
	char **ptr = session->args;

	while (session->args[i])
	{
		if (_isalpha(session->args[i][0]) || session->args[i][0] == '_')
		{
			foundVar = node_search_index(head, ptr[i]);
			if (foundVar > -1)
			{
				delete_node(&session->env_list, foundVar);
				return (1);
			}
		}
		i++;
	}
	errno = ENOSTRING;
	errorHandler(session);
	return (-1);
}

/**
 * _isalpha - checks if c is an alphabet
 * @c: potential alphabetical value
 * Return: if c is a letter, returns 1. Otherwise, return 0.
 */
int _isalpha(int c)
{
	if (c > 64 && c < 91)
		return (1);
	else if (c > 96 && c < 123)
		return (1);
	else
		return (0);
}
