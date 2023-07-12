#include "shell.h"

/**
  *_getline - reads a line of chars from a file pointer
  *@lineptr: pointer to buffer which line is stored
  *@n: size of the buffer where line is stored
  *@stream: pointer to the file where line is read from
  *Return: number of chars that was read
  */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t no_of_chars;
	size_t pos = 0;
	char *buffer = *lineptr, *new_buffer;

	if (!buffer || *n < 1)
	{
		buffer = malloc(BUFF_MAX);
		if (!buffer)
			return (-1);
		*n = BUFF_MAX;
		*lineptr = buffer;
	}
	do {
		no_of_chars = read(fileno(stream), buffer + pos, 1);
		if (no_of_chars == -1)
			return (-1);
		if (no_of_chars == 0)
			return (EOF);
		pos += no_of_chars;
		if (pos + 1 >= *n)
		{
			new_buffer = reallocate(buffer, *n, *n + 2);
			if (!new_buffer)
				return (-1);
			buffer = new_buffer;
			*n += 1;
			*lineptr = buffer;
		}
	} while (buffer[pos - 1] != '\n');
	buffer[pos] = '\0';
	return (pos);
}
