#include "shell.h"
/**
 * path_execute - execute a command in the path
 * @command: full path to the command
 * @vars: pointer to struct of variables
 * Return: 0 on success, 1 on failure
 */
int path_execute(char *command, vars_t *vars)
{
	/* check if command is executable */
	if (access(command, X_OK) != 0)
	{ /* print error message and set status */
		print_error(vars, ": Permission denied\n";
		vars->status = 126;
		return 0;
	
	}
	/* fork a child process */
	pid_t child_pid = fork();
	if (child_pid == -1)
	{ /* print error message and set status */
		print_error(vars, NULL);
		vars->status = 1;
		return 0;
	}

	/* if child process, execute the command */
	if (child_pid == 0)
	{
		if (execve(command, vars->av, vars->env) == -1
		{ /* print error message and exit */
			print_error(vars, NULL);
			exit(1);
		}
	}
	/* if parent process, wait for child process to finish */
	else
	{
		wait(&vars->status);
		/* set status based on exit status of child process */
		if (WIFEXITED(vars->status))
		{
			vars->status = WEXITSTATUS(vars->status);
		}
		else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
		{
			vars->status = 130;
		}
		else
		{
			vars->status = 1;
		}
		return 0;
	}
	/* if we get here, there was an error executing the command */
		vars->status = 1;
		return 0;
}
/**
 * find_path - finds the PATH variable
 * @env: array of environment variables
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *find_path(char **env)
{
	/* loop through environment variables */
	for (int i = 0; env[i] != NULL; i++)
	{ /* check if variable is "PATH" */
		if (strncmp(env[i], "PATH=", 5) == 0)
		{ /* return value of "PATH" variable */
			return env[i] + 5;
		}
	}
	/* "PATH" variable not found */
	return NULL;
}
/**
 * check_for_path - checks if the command is in the PATH
 * @vars: variables
 * Return: void
 */
void check_for_path(vars_t *vars)
{
	if (check_for_dir(vars->av[0]))
	{
		execute_cwd(vars);
		return;
	}
	char *path = find_path(vars->env);
	if (path != NULL)
	{
		char **path_tokens = tokenize(path + 5, ":");

		for (int i = 0; path_tokens[i] != NULL; i++)
		{
			char *command_path = _strcat(path_tokens[i], "/", vars->av[0]);
			if (access(command_path, X_OK) == 0)
			{
				path_execute(command_path, vars);
				free(command_path);
				free(path_tokens);
				return;
			}
			free(command_path);
		}
		free(path_tokens);
	}

	print_error(vars, ": not found\n");
	vars->status = 127;
	new_exit(vars);
}
/**
 * execute_cwd - executes the command in the current working directory
 * @vars: pointer to struct of variables
 * Return: 0 on success, 1 on failure
 */
int execute_cwd(vars_t *vars)
{
	struct stat buf:
		if (stat(vars->av[0], &buf) == -1)
	{
		print_error(vars, ": not found\n");
		vars->status = 127;
		return 0;
	}
	if (access(vars->av[0], X_OK) == -1)
	{
		print_error(vars, ": Permission denied\n");
		vars_status = 126;
		return 0;
	}
	pid_t child_pid = fork();
	if (child_pid == -1)
	{
		print_error(vars, NULL);
		return 0;
	}
	if (child_pid == 0)
	{
		if(execve(vars->av[0], vars->av, vars->env) == -1)
		{
			print_error(vars, NULL);
			exit(127);
		}
	}
	waitpid(child_pid, &vars->status, 0);
	if (WIFEXITED(vars->status))
	{
		vars->status = WEXITSTATUS(vars->status);
		return 0;
	}
	else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
	{
		vars->status = 130;
		return 0;
	}
	else
	{
		vars->status = 127;
		return 1;
	}
}
/**
 * check_for_dir - checks if the command is a part of a path
 * @str: command
 * Return: 1 on success, 0 on failure
 */
int check_for_dir(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return 1;
		str++;
	}
	return 0;
}


