#include "main.h"

/**
 * hsh_cd - Changes the directory
 * @args: Tpken arrays
 * @input_stdin: input stdin
 * @exit_status: Exit
 * Return: 1
 */

int hsh_cd(char **args, char *input_stdin, int *exit_status)
{
	int stat;
	char s[128];

	getcwd(s, sizeof(s));

	(void)input_stdin;
	(void)exit_status;

	if (args[1] == NULL)
		stat = chdir(getenv("HOME"));

	else if (strcmp(args[1], "-") == 0)
		stat = chdir(getenv("OLDPWD"));

	else if (strcmp(args[1], "~") == 0)
		stat = chdir(getenv("HOME"));

	else
		stat = chdir(args[1]);

	if (stat == -1)
		perror("cd had an error");

	setenv("OLDPWD", s, 1);

	setenv("PWD", getcwd(s, sizeof(s)), 1);
	return (1);
}

/**
 * hsh_setenv - Env variable
 * @args: array tokens
 * @input_stdin: input stdin
 * @exit_status: exit
 * Return: 1
 */

int hsh_setenv(char **args,  char *input_stdin, int *exit_status)
{
	int n_tokens = 0;

	(void)input_stdin;
	(void)exit_status;

	while (args[n_tokens] != NULL)
	{
		n_tokens++;
	}

	if (n_tokens == 3)
		setenv(args[1], args[2], 1);

	else if (n_tokens != 3)
		/*may need write command*/
	return (1);
}

/**
 * hsh_unsetenv - Delete an environment variable
 * @args: Array of tokens
 * @input_stdin: Input from stdin
 * @exit_status: Exit
 * Return: Return 1
 */

int hsh_unsetenv(char **args,  char *input_stdin, int *exit_status)
{
	int n_tokens = 0;

	(void)input_stdin;
	(void)exit_status;

	while (args[n_tokens] != NULL)
	{
		n_tokens++;
	}

	if (n_tokens == 2)
		unsetenv(args[1]);

	else if (n_tokens != 2)
		/*may need write command*/

	return (1);
}

/**
 * hsh_env - Function that print enviromental
 * @args: arguments
 * @input_stdin: input
 * @exit_status: exit status
 * Return: 1
 */

int hsh_env(char **args, char *input_stdin, int *exit_status)
{
	int i = 0;

	(void)args;
	(void)input_stdin;
	(void)exit_status;

	if (environ[i] == NULL)
	{
		/*May need write command here*/
		return (1);
	}
	for (i = 0; environ[i]; i++)
		/*may need write command here*/

	return (1);
}

/**
 * hsh_exit - Function exit
 * @args: arguments
 * @input_stdin: input of stdin
 * @exit_status: exit status
 * Return: exit
 */

int hsh_exit(char **args, char *input_stdin, int *exit_status)
{
	int output_exit = 0;

	(void)args;
	(void)input_stdin;
	(void)exit_status;

	if (args[1] == NULL)
	{
		free(args);
		free(input_stdin);
		exit(*exit_status);
	}
	if (args[2] != NULL)
	{
		/*may need write command*/
		return (0);
	}
	output_exit = atoi(args[1]);
	free(args);
	free(input_stdin);
	exit(output_exit);
}
