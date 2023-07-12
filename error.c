#include "shell.h"
/**
 * errorHandler - prints error message for shell
 * @session: the build config
 */
void errorHandler(shell *session)
{
	int len;
	static char error[BUFSIZE];
	char *ptr, *alpha;

	alpha = itoa(session->linecount);
	catenate(error, session->name);
	catenate(error, ": ");
	catenate(error, alpha);
	catenate(error, ": ");
	catenate(error, session->args[0]);
	catenate(error, getErrorMessage());
	if (session->args[1])
	{
		if (errno != EBADCD)
			catenate(error, ": ");
		catenate(error, session->args[1]);
	}
	catenate(error, "\n");
	ptr = char_locate('\n', error);
	len = ptr - error;
	write(STDERR_FILENO, error, len + 1);
	fflush(stdout);
	free(alpha);
	setnull(error, 0);
}

/**
 * getErrorMessage - matches errno to corresponding string
 * Return: string of error message
 */
char *getErrorMessage(void)
{
	char *str;

	switch (errno)
	{
		case EBADCD:
			str = ": can't cd to ";
			break;
		case (ENOENT):
			str = ": not found";
			break;
		case ENOSTRING:
			str = ": bad variable name";
			break;
		case EILLEGAL:
			str = ": Illegal number";
			break;
		case EWSIZE:
			str = ": invalid number of arguments";
			break;
		case ENOBUILTIN:
			str = ": type help for a list of built-ins";
			break;
		case EACCES:
			str = ": Permission denied";
			break;
		default:
			str = ": no error number assigned";
	}
	return (str);
}

/**
 * countDigits - count number of digits in a number
 * @num: input number
 * Return: number of digits
 */
unsigned int countDigits(int num)
{
	int digits = 0;

	while (num > 0)
	{
		digits++;
		num /= 10;
	}
	return (digits);
}

/**
 * itoa - converts integer to string
 * @num: input integer
 * Return: string type of number
 */
char *itoa(unsigned int num)
{
	int digits = 0;
	char *str;

	digits += countDigits(num);
	str = malloc(sizeof(char) * (digits + 1));
	if (!str)
	{
		perror("Malloc: failed\n");
		exit(errno);
	}
	setnull(str, digits);
	while (num > 0)
	{
		str[digits - 1] = num % 10 + '0';
		num = num / 10;
		digits--;
	}
	return (str);
}
