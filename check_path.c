#include "shell.h"
/**
  *check_path - searhes for the full path of a command
  *@session: shell information
  *
  *Return: void
  */
void check_path(shell *session)
{
	int i = 1, len, a = 0;
	char command[BUFF_MAX], *string = NULL;
	char *pathcopy = duplicate(session->pathway);
	char *token = tokenize(pathcopy, ":"), *str = session->args[0];

	i = access(str, X_OK);
	while (a < BUFF_MAX)
		setnull(command, a++);
	if (!i)
	{
		session->full_path = duplicate(str);
		free(pathcopy);
		return;
	}
	while (token)
	{
		len = length(token) + length(str) + 2;
		catenate(command, token);
		catenate(command, "/");
		catenate(command, str);
		setnull(command, (len - 1));
		i = access(command, X_OK);
		if (!i)
		{
			string = malloc(sizeof(char) * (length(command) + 1));
			copy(string, command);
			session->full_path = string;
			free(pathcopy);
			if (string == NULL)
				break;
			return;
		}
		setnull(command, 0);
		token = tokenize(NULL, ":");
	}
	free(pathcopy);
	session->full_path = duplicate(str);
}
