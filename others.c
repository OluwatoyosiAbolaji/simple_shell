#include "shell.h"
/**
 * reallocate - reallocates memory using malloc and free
 * @ptr: pointer to previously allocated memory
 * @size: size of ptr
 * @newsize: new size to be allocated to ptr
 * Return: buffer
 */
char *reallocate(char *ptr, size_t size, size_t newsize)
{
	size_t i, max = newsize;
	char *buffer, *clone;

	if (ptr == NULL)
	{
		buffer = malloc(newsize);
		return (buffer);
	}
	else if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (newsize == size)
	{
		return (ptr);
	}
	else
	{
		clone = ptr;
	}

	buffer = malloc(newsize);
	if (buffer == NULL)
		return (NULL);

	if (newsize > size)
		max = size;

	for (i = 0; i < max; i++)
	{
		buffer[i] = clone[i];
	}

	free(ptr);
	return (buffer);
}

/**
  *printline - prints a new line
  *Return: nothing
  */

void printline(void)
{
	write(STDOUT_FILENO, "\n", 1);
}
