#include "shell.h"

/**
 * _getenv - retrieves env variable that matches input string
 * @input: input string
 * @environ: local environmental variables
 * Return: string of env variable
 */
char *_getenv(char *input, char **environ)
{
	int i = 0;
	char *token, *path;

	while (environ[i])
	{

		token = tokenize(environ[i], "=");
		if (compare(token, input) == 0)
		{
			path = tokenize(NULL, "=");
			return (path);
		}
		i++;
	}
	return (NULL);
}
/**
  *convert_list_to_arr - converts a list to an array
  *@session: shell information
  *Return: void
  */
void convert_list_to_arr(shell *session)
{
	int i = 0;
	size_t count = 0;
	char **envList = NULL;
	list *tmp = session->env_list;

	count = listlength(tmp);
	envList = malloc((sizeof(char *)) * (count + 1));
	if (!envList)
	{
		perror("Malloc failed\n");
		exit(1);
	}
	while (tmp)
	{
		envList[i] = duplicate(tmp->string);
		tmp = tmp->next;
		i++;
	}
	envList[i] = NULL;
	session->env_strings = envList;

}
/**
 * delete_comment - deletes comments from input string
 * @string: input string
 * Return: void
 */
void delete_comment(char *string)
{
	int i = 0;
	int condition = 0;

	while (string[i])
	{
		if (i == 0 && string[i] == '#')
		{
			setnull(string, i);
			return;
		}
		if (condition)
		{
			if (string[i] == '#' && string[i - 1] == ' ')
			{
				setnull(string, i);
				return;
			}
		}
		i++;
		condition = 1;
	}
}

/**
 * execute_shell - executes a shell
 * @session: shell information
 */
void execute_shell(shell *session)
{
	while (1)
	{
		get_input(session);
		if (split_commands(session) == 0)
			continue;
		execute_commands(session);
	}
}
