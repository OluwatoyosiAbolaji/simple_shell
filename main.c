#include "shell.h"

/**
 * main - entry point for application
 * @ac: argument count
 * @av: argument vector
 * @environ: environmental variables
 * Return: 0 on success
 */
int main(int ac, char **av, char **environ)
{
	shell session;

	(void)ac;
	signal(SIGINT, signalhandle);
	initialize_shell(&session, environ);
	session.name = av[0];
	execute_shell(&session);
	return (0);
}

/**
  *signalhandle - escapes the sigint signal
  *@a: signal argument
  *Return: void
  */

void signalhandle(int a)
{
	(void)a;

	signal(SIGINT, signalhandle);
	printline();
	printprompt();
}

/**
  *initialize_shell - sets current shell information
  *@ptr: struct holding information
  *@environ: environmental variables
  *Return: Initialized shell
  */

void initialize_shell(shell *ptr, char **environ)
{
	int i;

	ptr->env_list = create_list(environ);
	ptr->env_strings = NULL;
	ptr->args = NULL;
	ptr->buffer = NULL;
	ptr->pathway = _getenv("PATH", environ);
	ptr->commands = NULL;
	ptr->full_path = NULL;
	ptr->linecount = 0;
	ptr->name = NULL;
	ptr->status = 0;
	for (i = 0; i < BUFF_MAX; i++)
		setnull(ptr->command_seperator, i);
}
