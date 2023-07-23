#include "shell.h"

/**
  *string_locate - locates the first occurrence of a string within a string
  *@search: string to be searched
  *@check: string to be checked
  *Return: index of the first occurrence of the checked string in the searched
  */

int string_locate(char *search, char *check)
{
	int i = 0;
	char *str = NULL, *ptr = NULL, *string = NULL;

	str = char_locate(check[i], search);
	while (str)
	{
		string = str;
		for (ptr = check; *ptr; string++, ptr++)
		{
			if (*ptr != *string)
				break;
		}
		if (!(*ptr))
			return (str - search);
		str++;
		str = char_locate(check[i], str);
	}
	return (-1);
}

/**
 * print_number - converts an integer to a string.
 * @n: The integer to be converted.
 * Return: number in string form
 */
char *print_number(int n)
{
	unsigned int num = n;
	char *string = NULL;
	int j = 10, i = 0;

	if (n < 0)
		num = -(num);
	for (i = 0; (num / j) > 0; j *= 10)
		i++;
	if (n < 0)
		string = malloc(sizeof(char) * (i + 3));
	else
		string = malloc(sizeof(char) * (i + 2));
	if (!string)
		return (NULL);
	if (n < 0)
	{
		string[i + 2] = '\0';
		string[0] = '-';
	}
	string[i + 1] = '\0';
	j = 10;
	while (i >= 0)
	{
		string[i--] = ((num % j) + '0');
		num /= 10;
	}
	return (string);
}
