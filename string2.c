#include "shell.h"
/**
 * char_locate - locates a character in a string
 * @string: string
 * @a: character
 * Return: pointer to first occurrence of c in s, or NULL if not found
 */
char *char_locate(char a, char *string)
{
	char *ptr = string;
	char c = a;

	while (*ptr)
	{
		if (*ptr == c)
		{
			return (ptr);
		}
		ptr++;
	}
	return (NULL);
}

/**
  * copy - Copy a string
  * @dest: Destination value
  * @src: Source value
  *
  * Return: the pointer to dest
  */
char *copy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i++] = '\0';

	return (dest);
}
/**
  *index_locate - check for the first occurrence of the second string in the
  *first
  *@search: string to be searched
  *@check: string to be checked
  *Return: returns the index in the first
  */
int index_locate(char *search, char *check)
{
	char c;
	char *ptr, *s;

	for (s = search, c = *s; c; s++, c = *s)
		for (ptr = check; *ptr; ptr++)
			if (c == *ptr)
				return (s - search);
	return (s - search);
}
/**
  *tokenize - seperate strings into tokens
  *@string: string to be tokenized
  *@delim: delimiter string
  *Return: tokenized string
  */

char *tokenize(char *string, char *delim)
{
	static char *last;
	char c;

	if (string == NULL)
		string = last;
	do {
		c = *string;
		string++;
		if (!c)
			return (NULL);
	} while (char_locate(c, delim));
	string--;
	last = string + index_locate(string, delim);
	if (*last)
	{
		*last = 0;
		last++;
	}
	return (string);
}

/**
  *split - seperates line into strings
  *@session: struct containing info about the present session
  *Return: True if splited and False if not
  */
int split(shell *session)
{
	int wordcount = 0, i;
	char *token, *delim = " \t";
	char *ptr = duplicate(session->buffer);
	int indicator = 0;

	for (i = 0; ptr[i]; i++)
	{
		if (ptr[i] == ' ' || ptr[i] == '\t')
			indicator = 0;
		else if (indicator == 0)
		{
			indicator = 1;
			wordcount++;
		}
	}
	if (wordcount == 0)
	{
		free(ptr);
		free(session->buffer);
		session->args = NULL;
		return (0);
	}
	session->args = malloc((sizeof(char *)) * (wordcount + 1));
	token = tokenize(ptr, delim);
	i = 0;
	while (token)
	{
		session->args[i] = duplicate(token);
		i++;
		token = tokenize(NULL, delim);
	}
	session->args[i] = NULL;
	free(ptr);
	return (1);
}
