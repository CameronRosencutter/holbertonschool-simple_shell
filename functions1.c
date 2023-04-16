#include "shell.h"
/**
 * check_for_builtins - checks if the command is a builtin
 * @vars: variables
 * Return: pointer to the function or NULL
 */

/* an array of structs to hold the names and function pointers of the built-in commands */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *vars);
}
builtins_t;
/* define function that takes a pointer to a struct called "vars_t" as it's argument
 * and returns a pointer to a function that takes a pointer to a struct called "vars_t" as its argument */
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int i;
/* initialize the array of built-in commands */
	builtins_t check[] =
	{
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};
/* loop through the array of built-in commands and check if the first argument matches any of them */
	for (i = 0; check[i].f != NULL; i++)
	{
		if (_strcmpr(vars->av[0], check[i].name) == 0)
			break;
	}
/* if a match is found, execute the corresponding built-in function and it's return pointer */
	if (check[i].f != NULL)
		check[i].f(vars);

	return (check[i].f);
}
/**
 * new_exit - takes a pointer to a struct called "vars_t" as its argument
 * @vars: variables
 * Return: void
 */
void new_exit(vars_t *vars)
{
	int status;
/* check if the first argument is "exit" and a second argument exists */
	if (_strcmpr(vars_>av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		/*convert the second argument to an integer using the "_atoi" function */
		status = _atoi(vars->av[1]);
/* if the conversion is successful, set the exit status of the program to the integer value */
		if (status != -1)
			vars->status = status;
		/* if the conversion fails, set the exit status to 2 and print an error message */
		else
		{
			vars->status = 2;
			print-error(vars, ": Illegal number: ");
			_puts2(vars->av[1]);
			_puts2("\n");
		}
	}
/* free memory allocated for the buffer, arguments, command lists, and environment variables */
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
/* exit the program with the exit status */
	exit(vars->status);
}

/** _env - prints the current environment
 * @vars: struct of variables
 * Return: void
 */
void _env(vars_t *vars)
{
	unsigned int i;
/* loop through the environment variables in the "vars" struct using a "for" loop */
	for (i = 0; vars->[i]; i++)
	{
/* print each environment variable to the standard output using the "_puts" function */
		_puts(vars->env[i]);
		_puts("\n");
	}
/* set the exit status of the program to 0 */
	vars->status = 0;
}

/**
 * new_setenv - create a new environment variable or edit and existing variable
 * @vars: pointer to struct of variables
 * Return: void
 */
void new_setenv(vars_t *vars)
{
	char **key;
	char *var;
/* check if the second and third arguments of the function are not NULL */
	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
/* if they are NULL, print an error messange and set the exit status of the program to 2 */
		print_errors(vars, ": Incorrect number of argments\n");
		vars>status = 2;
		return;
	}
/* call a function called "find_key" to search for the key in the environment variables */
	key = find_key(vars->env, vars->[1]);
/* if the key is not found, call a function called "add_key" to add a new environment variable to the list */
	if (key == NULL)
		add_key(vars);
	else
	{
/* if the key is found, call a function called "add_value" to add a new value to the existing environment variable */
		var = add_value(vars->av[1], vars->[2]);
/* if "add_value" returns NULL, print an error message, free the memory allocated for the variables, and exit
 * the program with an exit status of 127 */
		if (var == NULL)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
/* free the memory alloocated for the "key" variable */
		free(*key);
		*key = var;
	}
/* set the exit status of the program to 0 */
	vars->status = 0;
}

/**
 * new_unsetenv - remove an environment variable
 * @vars: pointer to a struct of variables
 * Return: void
 */
void new_unsetenv(vars_t *vars)
{
	if (vars->av[1] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}

	char **key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
	{
		print_error(vars, ": No variable to unset");
		return;
	}

	while (*key != NULL)
	{
		*key = *(key + 1);
		key++;
	}

	vars->status = 0;
}

