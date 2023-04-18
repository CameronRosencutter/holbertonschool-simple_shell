#include "shell.h"


/**
 * _getline - function that used to read a string or a line
 * Return: 0
 */
int _getline(void)
{
	size_t size;
	int i;
	size_t bytes_read = 0;

	char *string = (char *)malloc(50 * sizeof(char));

	if (bytes_read == (size_t)-1)
	{
		puts("hsh");
	}
	else
		for (i = 0; i < 1; i++)
		{
			printf("$ ");
			bytes_read = getline(&string, &size, stdin);
		}
	return (0);
}
/**
 * _strtok - function that used to read a string or a line
 * Return: 0
 */
int _strtok(void)
{
	char *str = " ";
	char *token = strtok(str, " ");

	while (token != NULL)
	{
		printf("%s", token);
		token = strtok(NULL, " ");
	}
	return (0);
}
/**
* _fork - creating a new process
*Return: void
*/
void _fork(void)
{
	char *argv[] = {"/bin/ls", "-l", ".", NULL};

	pid_t pid = fork();

	if (pid == 0)
	{
		execve(argv[0], argv, NULL);
	}
	else
	{
		wait(NULL);
	}
}
/**
* sig_handler - checks if Ctrl C is pressed by the input
* @signum: int
*Return: void
*/
void sig_handler(int signum)
{

	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n$ ", 3);
	}
}
