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
