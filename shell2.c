#include "shell.h"

/**
  *printprompt - prints the prompt
  *Return: void
  */
void printprompt(void)
{
	write(STDERR_FILENO, "peter$ ", 7);
	fflush(stdout);
}

/**
  *get_input - gets and screens input to the program
  *@session: pointer to shell information
  *Return: void
  */
void get_input(shell *session)
{
	int len;
	size_t buffersize = 0;
	char *ptr;

	session->args = NULL;
	session->env_strings = NULL;
	session->linecount++;
	if (isatty(STDIN_FILENO))
		printprompt();
	len = _getline(&session->buffer, &buffersize, stdin);
	if (len == EOF)
	{
		freeall(session);
		free(session->buffer);
		if (session->status)
			exit(session->status);
		exit(EXIT_SUCCESS);

	}
	set_home(session);
	ptr = char_locate('\n', session->buffer);
	if (ptr)
		setnull(ptr, 0);
	delete_comment(session->buffer);
}

/**
  *new_process - initiates a new process
  *@session: pointer to shell information
  *Return: 0 on success, -1 on failure
  */
int new_process(shell *session)
{
	int status, i = 0, pid;

	convert_list_to_arr(session);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error\n");
		freeargs(session->args);
		freeargs(session->env_strings);
		exit(1);
	} else if (pid == 0)
	{
		i = execve(session->full_path, session->args, session->env_strings);
		if (i == -1)
		{
			errorHandler(session);
			freeargs(session->args);
			freeargs(session->env_strings);
			if (errno == ENOENT)
				exit(127);
			if (errno == EACCES)
				exit(126);
		}
	} else
	{
		wait(&status);
		if (WIFEXITED(status))
			session->status = WEXITSTATUS(status);
		free(session->full_path);
		freeargs(session->env_strings);
	}
	if (session->status == 127 || session->status == 126)
	{
		freeargs(session->args);
		return (0);
	}
	return (1);
}

/**
  *set_home - changes ~ to the home directory name
  *@session: shell info
  *Return: 0 on success, -1 on failure
*/

int set_home(shell *session)
{
	int index;
	char *buffer = NULL, *str = NULL;
	char *string = NULL, *ptr = NULL, *newptr = NULL;

	ptr = char_locate('~', session->buffer);
	if (!ptr)
		return (0);
	index = node_search_index(session->env_list, "HOME");
	if (index == -1)
		return (index);
	string = getNodeAtIndex(session->env_list, index);
	str = char_locate('=', string);
	str++;
	*ptr = 0;
	ptr++;
	buffer = session->buffer;
	newptr = malloc(length(buffer) + length(str) + length(ptr) + 1);
	setnull(newptr, 0);
	catenate(newptr, buffer);
	catenate(newptr, str);
	catenate(newptr, ptr);
	free(string);
	session->buffer = newptr;
	free(buffer);
	return (0);
}
