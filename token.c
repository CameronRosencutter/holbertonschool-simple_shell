#include "shell.h"

/**
 * tokenize - tokenizes a buffer
 * @buffer: buffer token
 * @delimiter: delimiter
 * Return: pointer
 */

char **tokenize(char *buffer, char *delimiter)
{
	if (buffer == NULL)
		return (NULL);

	size_t mcount = 10;
	char **tokens = malloc(mcount * sizeof(char *));
	if (tokens == NULL)
		return (NULL);

	size_t i;
	for (i = 0; i < mcount; i++)
	{
		tokens[i] = new_strtok(buffer, delimiter);
		if (tokens[i] == NULL)
			break;
		buffer = NULL;
	}

	 if (i == mcount)
	 {
		 mcount *= 2;
		 char **new_tokens = realloc(tokens, mcount * sizeof(char *));
		  if (new_tokens != NULL)
			   tokens = new_tokens;
	 }

	 return (tokens);
}
