#include "shell.h"
/**
  *env - prints all environmental variables in a shell
  *@session: shell info
  *Return: number of variables
  */

int env(shell *session)
{
	int i;

	i = nodesprint(session->env_list);
	return (i);
}
/**
 * findbuiltin - validates if command is builtin and executes if true
 * @session: shell info
 * Return: 1 if found, 0 if not
 */
int findbuiltin(shell *session)
{
	int i = 0;
	builtin getBuiltIns[] = {
		{"exit", exitf},
		{"env", env},
		{"setenv", setenvFunc},
		{"unsetenv", unsetenvFunc},
		{"cd", cd},
		{NULL, NULL}
	};

	while (getBuiltIns[i].string)
	{
		if (compare(session->args[0], getBuiltIns[i].string) == 0)
		{
			getBuiltIns[i].func(session);
			freeargs(session->args);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * exitf - exits the application
 * @session: shell info
 * Return: 1 on success, 0 on failure
 */
int exitf(shell *session)
{
	int argCount, exitStatus;

	argCount = countargs(session->args);
	if (argCount == 1)
	{
		freeall(session);
		freeargs(session->commands);
		write(STDOUT_FILENO, "logout\n", length("logout\n"));
		if (session->status)
			exit(session->status);
		exit(EXIT_SUCCESS);
	}
	else if (argCount > 1)
	{
		exitStatus = _atoi(session->args[1]);
		if (exitStatus == -1)
		{
			errno = EILLEGAL;
			session->status = 2;
			errorHandler(session);
			return (0);
		}
		freeall(session);
		freeargs(session->commands);
		write(STDOUT_FILENO, "exit\n", length("exit\n"));
		exit(exitStatus);
	}
	return (1);
}

/**
* countargs - count the number of arguments
* @args: input array of strings
* Return: number of strings
*/
int countargs(char **args)
{
	int i = 0;

	while (args[i])
		i++;
	return (i);
}

/**
* _atoi - change string to an integer
* @s: input string
* Return: -1 if it's not a valid number, else the converted number
*/
int _atoi(char *s)
{
	int i = 0;
	unsigned long num = 0;

	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			num = (num * 10) + (s[i] - '0');
		else
			return (-1);
		i++;
	}
	if (num > INT_MAXI)
	{
		return (-1);
	}
	return (num);
}
