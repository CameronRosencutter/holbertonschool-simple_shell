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
 * delete_env_variable - deletes environment variable
 */

int delete_env_variable(const char *name)
{
    /* Find the environment variable manually*/
    size_t name_len = strlen(name);
    char **envp = environ;
    while (*envp != NULL)
    {
        if (strncmp(*envp, name, name_len) == 0 && (*envp)[name_len] == '=')
	{
            break;  /* found it!*/
        }
        envp++;
    }
    if (*envp == NULL)
    {
        perror("no such variable");
        return 1;  /* indicate failure*/
    }

    /* Use unsetenv to delete the environment variable*/
    if (unsetenv(name) != 0)
    {
        perror("unsetenv");
        return 1;  /* indicate failure */
    }

    return 0;  /* indicate success*/
}

/**
 * hsh_setenv - Set enviroment Variable
 */

int hsh_setenv(char **args, char *input_stdin, int *exit_status)
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
		write(STDERR_FILENO, "hsh: setenv: wrong number of arguments\n", 41);
	return (1);
}

/**
 * myFunction() - exit
 */

int myFunction()
{
	return 2;
}
