#include "shell.h"

/**
  *check_variables - checks for variables and expands them
  *@session: shell information
  *Return: 1 on success, -1 on failure
  */

int check_variables(shell *session)
{
	char *ptr = NULL;
	int i = 0, j = 0, result;

	while (session->args[i])
	{
		ptr = session->args[i];
		j = 0;
		while (ptr[j])
		{
			if (ptr[j] == '$' && ptr[j - 1] != '\\')
			{
				ptr[j] = '\0';
				if (ptr[j + 1] == '$' && ptr[j] != '\\')
					result = replace_pid(session, ptr, i);
				else if (ptr[j + 1] == '?')
					result = replace_exit(session, ptr, i);
				else
					result = replace_variable(session, ptr, i);
				if (result == -1)
					return (result);
			}
			j++;
			ptr = session->args[i];
		}
		i++;
	}
	return (1);
}

/**
  *replace_variable - expands variables found in linked list
  *@session: shell information
  *@ptr: argument containing variable
  *@index: index of argument
  *Return: 0 on success, -1 on failure, 1 if no variable
  */

int replace_variable(shell *session, char *ptr, int index)
{
	char *str = ptr + length(ptr) + 1, *string = NULL;
	char *token = NULL, *newptr = NULL;
	list *node = session->env_list;
	int len;

	while (node->string)
	{
		string = duplicate(node->string);
		token = tokenize(string, "=");
		if (token == NULL)
			return (-1);
		if (string_locate(str, token) == 0)
		{
			str += length(token);
			token = tokenize(NULL, "=");
			len = length(ptr) + length(token) + length(str);
			newptr = malloc(sizeof(char) * (len + 1));
			if (newptr == NULL)
				return (-1);
			copy(newptr, ptr);
			catenate(newptr, token);
			if (*str)
				catenate(newptr, str);
			session->args[index] = newptr;
			free(ptr);
			free(string);
			return (0);
		}
		free(string);
		node = node->next;
		if (!node)
			break;
	}
	return (1);
}

/**
  *replace_pid - expands $$ to current process id
  *@session: shell information
  *@ptr: argument containing variable
  *@index: index of argument
  *Return: 0 on success, -1 on failure
  */

int replace_pid(shell *session, char *ptr, int index)
{
	char *str = ptr + length(ptr) + 2, *string = NULL;
	char *newptr = NULL;
	int len, pid;

	pid = getpid();
	string = print_number(pid);
	len = length(string) + length(str) + length(ptr);
	newptr = malloc(sizeof(char) * (len + 1));
	if (newptr == NULL)
		return (-1);
	copy(newptr, ptr);
	catenate(newptr, string);
	if (*str)
		catenate(newptr, str);
	session->args[index] = newptr;
	free(string);
	free(ptr);
	return (0);
}

/**
  *replace_exit - expands $? to the last exit status
  *@session: shell information
  *@ptr: argument containing variable
  *@index: index of argument
  *Return: 0 on success, -1 on failure
  */

int replace_exit(shell *session, char *ptr, int index)
{
	char *str = ptr + length(ptr) + 2, *string = NULL;
	char *newptr = NULL;
	int len;

	string = print_number(session->status);
	if (string == NULL)
		return (-1);
	len = length(string) + length(str) + length(ptr);
	newptr = malloc(sizeof(char) * (len + 1));
	if (newptr == NULL)
		return (-1);
	copy(newptr, ptr);
	catenate(newptr, string);
	if (*str)
		catenate(newptr, str);
	session->args[index] = newptr;
	free(string);
	free(ptr);
	return (0);
}
