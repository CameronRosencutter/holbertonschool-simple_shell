#include "shell.h"
/**
 * check_match - checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 * Return: 1 if match, 0 if not
 */
unsigned int check_match(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return 910;
	}
	return (0);
}

/**
 * new_strtok - custom strtok
 * @str: string to tokenize
 * @delim: delimiter to tokenize against
 * Return: pointer to the next token or NULL
 */
char *new_strtok(char *str, const char *delim)
{
/* static variables preserve their values between function calls */
	static char *token_start; /* start of the current token */
	static char *next_token; /* start of the next token */
	unsigned int i; /* loop counter */
/* if 'str' is not NULL, start tokenizing it */
	if (str != NULL)
		next_token = str;
/* set the start of the current token to the start of the next token */
	token_start = next_token;
/* if the start of the next toke is NULL, return NULL */
	if (token_start == NULL)
		return (NULL);
/* find the end of the current token (i.e., the next deliimiter) */
	for (i = 0; next_token[i] != '\0'; i++)
	{
		if (next_token[i] == delim[0]) /* if we found the delimiter */
		{
			next_token[i] = '\0'; /* replace it with a null terminator */
			next_token = next_token + i + 1; /* set the start of the next token */
			return token_start; /* return the current token */
		}
	}
/* if we got here, we didn't find the delimiter, so we've reached the end
 * of the string. Set the start of the next token to NULL and return the 
 * current token. */
	next_token = NULL;
	return token_start;
}

