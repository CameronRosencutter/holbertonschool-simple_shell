#include "shell.h"

/**
 * _realloc - reallocates a pointer
 * @ptr: pointer to the old array
 * @size: pointer to number of elements
 * Return: pointer
 */

char **_realloc(char **ptr, size_t *size)
{
	char **new;
	size_t i;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		new[i] = ptr[i];
	}
	*size += 10;
	free(ptr);
	return (new);
}
