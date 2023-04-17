#include "shell.h"

/**
 * _puts - writes a string to standard output
 * @str: string
 * Return: Characters
 */

ssize_t _puts(char *str)
{
	ssize_t num = _strlen(str);
	ssize_t len = write(STDOUT_FILENO, str, num);

	return (len);
}

/**
 * _strdup - returns pointer
 * @strtodup: string to be duplicated
 * Return: pointer
 */

char *_strdup(char *input_string)
{
	if (input_string == NULL)
	{
		return (NULL);
	}

	int length = 0;

	while (input_string[length] != '\0')
	{
		length++;
	}

	 char *copy = malloc((length + 1) * sizeof(char));
	 for (int i = 0; i <= length; i++)
	 	{
			copy[i] = input_string[i];
	 	}
	 return (copy);
}

/**
 * _strcmpr - compares two strings
 * @strcmp1: first string
 * @strcmp2: second string
 * Return: 0
 */

int _strcmpr(char *strcmp1, char *strcmp2)
{
	int i = 0;

	while (strcmp1[i] == strcmp2[i] && strcmp1[i] != '\0')
	{
		i++;
	}

	if (strcmp1[i] == strcmp2[i])
	{
		return (0);
	}
	else
	{
		return (strcmp1[i] - strcmp2[i]);
	}
}

/**
 * _strcat - concentrate 2 strings
 * @strc1: first string
 * @strc2: second string
 * Return: pointer
 */

char *_strcat(char *strc1, char *strc2)
{
	unsigned int len1 = 0, len2 = 0, i, j;
	char *newstring;

	if (strc1 != NULL)
	{
		while (strc1[len1] != '\0')
		{
			len1++;
		}
	}
	if (strc2 != NULL)
	{
		while (strc2[len2] != '\0')
		{
			len2++;
		}
	}

	newstring = malloc((len1 + len2 + 2) * sizeof(char));
	if (newstring == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < len1; i++)
	{
		newstring[i] = strc1[i];
	}
	newstring[i++] = '/';
	for (j = 0; j < len2; j++)
	{
		newstring[i + j] = strc2[j];
	}
	newstring[i + j] = '\0';
	return (newstring);
}

/**
 * _strlen - returns the length
 * @str: string
 * Return: string length
 */

unsigned int _strlen(char *str)
{
	unsigned int len;


	len = 0;

	for (len = 0; str[len]; len++);

	return (len);
}
