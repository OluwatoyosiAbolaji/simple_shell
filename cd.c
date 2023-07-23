#include "shell.h"

/**
  *cd - changes the directory
  *@session: shell info
  *Return: 1 on success
  */

int cd(shell *session)
{
	int i = 0, result = 1;

	while (session->args[i])
		i++;
	if (i > 2)
	{
		errno = EWSIZE;
		errorHandler(session);
		return (-1);
	}
	else if (i == 1)
		result = cdhome(session);
	else if (i == 2 && (compare(session->args[1], "-") == 0))
		result = cdprevious(session);
	else
	{
		i = chdir(session->args[1]);
		if (i < 0)
		{
			errno = EBADCD;
			errorHandler(session);
			return (-1);
		}
	}
	updateEnviron(session);
	return (result);
}

/**
  *cdhome - changes directory to the home directory
  *@session: shell info
  *Return: 1 on success
  */

int cdhome(shell *session)
{
	char *string = NULL, *ptr = NULL;
	int index;

	index = node_search_index(session->env_list, "HOME");
	if (index == -1)
		return (-1);
	string = getNodeAtIndex(session->env_list, index);
	ptr = char_locate('=', string);
	ptr++;
	index = chdir(ptr);
	if (index < 0)
	{
		errno = EBADCD;
		errorHandler(session);
		return (-1);
	}
	free(string);
	return (1);
}

/**
  *cdprevious - changes directory to the previous directory
  *@session: shell info
  *Return: 1 on success
  */

int cdprevious(shell *session)
{
	int i;
	char *str, *ptr;
	char *current = NULL;

	current = getcwd(current, 0);
	i = node_search_index(session->env_list, "OLDPWD");
	if (i == -1)
	{
		chdir(current);
		write(STDOUT_FILENO, current, length(current));
		printline();
		free(current);
		return (-1);
	}
	str = getNodeAtIndex(session->env_list, i);
	ptr = char_locate('=', str);
	ptr++;
	chdir(ptr);
	write(STDOUT_FILENO, ptr, length(ptr));
	printline();
	free(str);
	free(current);
	return (1);
}

/**
  *updateEnviron - updates the environmental variables
  *@session: shell info
  *Return: returns 1 on success
  */

int updateEnviron(shell *session)
{
	int i;

	i = updateprev(session);
	updatenext(session);
	return (i);
}
