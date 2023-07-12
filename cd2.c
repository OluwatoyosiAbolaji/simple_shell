#include "shell.h"

/**
  *updateprev - changes the previous pwd
  *@session: shell info
  *Return: 1 on success
  */

int updateprev(shell *session)
{
	static char buffer[BUFF_MAX];
	char *string = NULL;
	int index;

	index = node_search_index(session->env_list, "PWD");
	if (index == -1)
		return (index);
	string = getNodeAtIndex(session->env_list, index);
	catenate(buffer, "OLD");
	catenate(buffer, string);
	free(string);
	index = node_search_index(session->env_list, "OLDPWD");
	if (index == -1)
		return (index);
	delete_node(&session->env_list, index);
	nodeatindex(&session->env_list, index, buffer);
	setnull(buffer, 0);
	return (index);
}

/**
  *updatenext - changes the current pwd
  *@session: shell info
  *Return: 1 on success
  */

int updatenext(shell *session)
{
	static char buffer[BUFF_MAX], buffer2[BUFF_MAX];
	int index;

	getcwd(buffer, sizeof(buffer));
	catenate(buffer2, "PWD=");
	catenate(buffer2, buffer);
	index = node_search_index(session->env_list, "PWD");
	if (index > -1)
	{
		delete_node(&session->env_list, index);
		nodeatindex(&session->env_list, index, buffer2);
	}
	else
		nodeatindex(&session->env_list, index, buffer);
	setnull(buffer, 0);
	setnull(buffer2, 0);
	return (index);
}
