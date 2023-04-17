#include "shell.h"

/**
 * make_env - make the shell environment
 * @env: environment
 * Return: pointer
 */

char **make_env(char **env)
{
	int count = 0;

	while (env[count] != NULL)
	{
		count++;
	}
	char **newenv = (char **) malloc(sizeof(char *) * (count + 1));

	if (newenv == NULL)
	{
		newenv[i] = env[i];
	}
	newenv[count] = NULL;

	return (newenv);
}

/**
 * free_env - free the shell's environment
 * @env: shells enviroment
 * Return: void
 */
void free_env(char **env)
{
	unsigned int i;

	for (i = 0; env[i] != NULL; i++)
		free(env[i]);
	free(env);
}
