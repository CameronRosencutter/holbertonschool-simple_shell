#include "shell.h"
/**
 * path_execute - execute a command in the path
 * @command: full path to the command
 * @vars: pointer to struct of variables
 * Return: 0 on success, 1 on failure
 */
int path_execute(char *command, vars_t *vars)
{
	if (access(command, X_OK) != 0)
	{
		print_error(vars, ": Permission denied\n");
		vars->status = 126;
		return (0);
	}
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		print_error(vars, NULL);
		vars->status = 1;
		return (0);
	}
	/* if child process, execute the command */
	if (child_pid == 0)
	{
		execve(command, vars->av, vars->env);
		print_error(vars, NULL);
		exit(1);
	}
	/* if parent process, wait for child process to finish */
	wait(&vars->status);
	/* set status based on exit status of child process */
	if (WIFEXITED(vars->status))
	{
		vars->status = WEXITSTATUS(vars->status);
	}

	else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
	{
		vars->statu = 130;
	}
	else
	{
		vars->status = 1;
	}
	return (0);
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
			return (env[i] + 5);
		}
	}
	/* "PATH" variable not found */
	return (NULL);
}
/**
 * check_for_path - checks if the command is in the PATH
 * @vars: variables
 * Return: 0 on success, 1 on failure
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
 * @av: an array of strings containing the command and its arguments
 * @env: the environment variable
 * Return: 0 on success, 1 on failure
 */
int execute_cwd(char **av, char **env)
{
	pid_t child_pid;

	if (access(av[0], F_OK) != 0)
	{
		print_error(av[0], ": not found\n");
		return (127);
	}
	if (access(av[0], X_OK) != 0)
	{
		print_error(av[0], ": Permission denied\n");
		return (126);
	}
	child_pid = fork();

	if (child_pid == -1)
	{
		print_error(NULL, "fork failed\n");
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(av[0], av, env) == -1)
		{
			print_error(av[0], ": not found\n");
			exit(127);
		}
	}
	wait(NULL);
	if (WIFEXITED(child_pid))
	{
		return (WEXITSTATUS(child_pid));
	}
	else if (WIFSIGNALED(child_pid) && WTERMSIG(child_pid) == SIGINT)
	{
		return (130);
	}
	return (1);
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
			return (1);
		str++;
	}
	return (0);
}


