#include "shell.h"
/**
 * add_key - create a new environment variable
 * @vars: pointer to struct of variables
 * Return: void
 */
void add_key(vars_t *vars)
{
	unsigned int i;
	char **newenv;
/* count the number of existing environment variables */
	for (i = 0; vars->env[i] != NULL; i++);
/* allocate memory for a new environment array with room for a new variable */
	newenv = malloc(sizeof(char *) * (i + 2));

	if (newenv == NULL)
	{
/* if malloc fails, print an error message and exit the program */
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
/* copy all existing environment variables into the new array */
	for (i = 0; vars->env[i] != NULL; i++)
		newenv[i] = vars->env[i];
/* add the new environment variable to the end of the new array */
	newenv[i] = add_value(vars->av[1], vars->av[2]);
	if (newenv[i] == NULL)
	{
/* if adding new variable fails, print an error message and exit the program */
		print_error(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		free_env(vars->env);
		free(newenv);
		exit(127);
	}
/* terminate the new environment array with NULL */
	newenv[i + 1] = NULL;
/* free the old environment array and set the pointer to the new array */
	free(vars->env);
	vars->env = newenv;
}

/**
 * find_key - finds an environment variable
 * @env: array of environment variables
 * @key: environment variable to find
 * Return: pointer to address of the environment variable
 */
char **find_key(char **env, char *key)
{
	unsigned int i, j, len;
/* get length of key */
	len = _strlen(key);
/* iterate through the environment variables */
	for (i = 0; env[i] != NULL; i++)
	{
/* compare each character of the key to the current environment variable */
		for (j = 0; j < len; j++)
			if (key[j] != env[i][j])
				break;
/* if the key is found, return a pointer to its address */
		if (j == len && env[i][j] == '=')
			return (&env[i]);
	}
/* key not found, return NULL */
	return (NULL);
}

/**
 * add_value - create a new environment variable string
 * @key: variable name
 * @value: variable value
 * Return: pointer to the new string;
 */
char *add_value(char *key, char *value)
{
	unsigned int len1, len2, i, j;
	char *new;
/* get length of key and value */
	len1 = _strlen(key);
	len2 = _strlen(value);
/* allocate memory for new string */
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
		return (NULL);
/* copy key and value to new string, separated by '=' */
	for (i = 0; key[i] != '\0\; i++)
		new[i] = key[i];
	new[i] = '=';
	for (j = 0; value[j] != '\0'; j++)
		new[i + 1 + j] = value[j];
	new[i + 1 + j] = '\0';

	return (new);
}

/**
 * _atoi - converts a string into an integer
 * @str: string to convert
 * Return: the integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
	unsigned int i, digits;
	int num = 0, num_test;
/* determine maximum number of digits an int can have */
	num_test = INT_MAX;
	for (digits = 0; num_test != 0; digits++)
		num_test /= 10;
/* iterate over each character in the string */
	for (i = 0; str[i] != '\0' && i < digits; i++)
	{
		num *= 10; /* shift existing digits left by one position */
/* check if the character is a digit */
		if (str[i] < '0' || str[i] > '9')
			return (-1);
/* add the digit to the number */
		num += str[i] - '0';
/* check for overflow */
		if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
			return (-1);
		if ((i == digits - 2) && (str[i + 1] != '\0') && (num . INT_MAX / 10))
			return(-1);
	}
/* check if there are extra characters in the string */
	if (i > digits)
		return (-1);
/* return the final number */
	return (num);
}

