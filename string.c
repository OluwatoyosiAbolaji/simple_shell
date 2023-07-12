#include "shell.h"

/**
  *length - calculates the number of chars of a string
  *@string: string to be calculated
  *
  *Return: no of characters in a string
  */

int length(char *string)
{
	int i;

	if (string == NULL)
		return (0);
	for (i = 0; string[i];)
		i++;
	return (i);
}

/**
  *duplicate - makes a copy of a string
  *@string: string to be duplicated
  *
  *Return: returns a pointer to a string duplicate
  */

char *duplicate(char *string)
{
	int i = 0;
	char *ptr = malloc((sizeof(char)) * (length(string) + 1));

	for (i = 0; string[i]; i++)
		ptr[i] = string[i];
	setnull(ptr, i);
	return (ptr);
}

/**
  *catenate - joins two strings together in one
  *@begin: beginning string
  *@end: ending string
  *
  *Return: returns a pointer to the new string
  */

char *catenate(char *begin, char *end)
{
	int i;
	char *ptr = begin + length(begin);

	for (i = 0; end[i]; i++)
	{
		ptr[i] = end[i];
	}
	setnull(ptr, i);
	return (begin);
}
/**
  *compare - compares two strings
  *@a: first string
  *@b: second string
  *Return: difference in ASCI Value
  */
int compare(char *a, char *b)
{
	while (*a)
	{
		if (*a != *b)
			break;
		a++;
		b++;
	}
	return (*(unsigned char *)a - *(unsigned char *)b);
}
/**
  *setnull - sets a byte of a string to null
  *@string: known string
  *@index: index to be set
  */

void setnull(char *string, int index)
{
	string[index] = 0;
}
