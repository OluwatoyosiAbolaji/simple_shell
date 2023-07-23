#include "shell.h"

/**
  *split_commands - seperates different commands
  *@session: shell info
  *Return: number of commands
  */

int split_commands(shell *session)
{
	char *delim = ";|&", *string = session->buffer;
	int i = 0, j = 0, command_count = 0, num = 0;

	while (session->buffer[i])
	{
		if (string[i] == ';')
		{
			session->command_seperator[num++] = string[i];
			j = 0;
		} else if (string[i] == '&' || string[i] == '|')
		{
			if (string[i + 1] == string[i])
			{
				session->command_seperator[num++] = string[i];
				i++;
			}
			j = 0;
		} else if (j == 0)
		{
			j = 1;
			command_count += 1;
		}
		i++;
	}
	if (command_count == 0)
	{
		free(session->buffer);
		return (command_count);
	}
	if (!(create_doubleptr(command_count, session, delim)))
		return (0);
	return (command_count);
}

/**
  *create_doubleptr - creates a pointer of pointers
  *@number: number of elements inside the pointer array
  *@session: shell information
  *@delim: delimiter
  *Return: double pointer or NULL
  */

char **create_doubleptr(int number, shell *session, char *delim)
{
	int i = 0;
	char **str = NULL, *ptr = NULL;

	str = malloc(sizeof(char *) * (number + 1));
	if (str == NULL)
	{
		free(session->buffer);
		return (NULL);
	}
	ptr = tokenize(session->buffer, delim);
	while (ptr)
	{
		str[i] = duplicate(ptr);
		ptr = tokenize(NULL, delim);
		i++;
	}
	str[i] = NULL;
	session->commands = str;
	return (str);
}

/**
  *execute_commands - executes the commands passed one by one
  *@session: shell info
  *Return: 0 on success, -1 on failure
  */
int execute_commands(shell *session)
{
	int i = 0, result, num = 0;

	for (i = 0; session->commands[i]; i++)
	{
		if (i == 0)
		{
			result = execute_command(session, session->commands[i]);
			if (result == -1)
				return (result);
		} else if (session->command_seperator[num] == '|' && !result)
		{
			result = execute_command(session, session->commands[i]);
			if (result == -1)
				return (result);
			num++;
		} else if (session->command_seperator[num] == '&' && result)
		{
			result = execute_command(session, session->commands[i]);
			if (result == -1)
				return (result);
			num++;
		} else if (session->command_seperator[num++] == ';') 
		{
			result = execute_command(session, session->commands[i]);
			if (result == -1)
				return (result);
		}
	}
	for (i = 0; i < BUFF_MAX; i++)
		setnull(session->command_seperator, i);
	free(session->buffer);
	freeargs(session->commands);
	return (0);
}

/**
  *execute_command - executes one command
  *@session: shell info
  *@command: command to be executed
  *Return: 1 on success, -1 or 0 on failure
  */

int execute_command(shell *session, char *command)
{
	int i;

	if (split(session, command) == 0)
		return (-1);
	i = findbuiltin(session);
	if (i == 1)
		return (i);
	check_path(session);
	i = new_process(session);
	if (!i)
		return (0);
	freeargs(session->args);
	return (1);
}

