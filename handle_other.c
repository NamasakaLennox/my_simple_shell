#include "main.h"
char pid_str[32], exit_str[32];

/**
 * handle_other - handles other commands that are not in PATH
 * @command: array of tokenized user commands
 * @user_input: raw input from the user
 * @exit_status: the exit status of the last command
 * @env: the environment variable passed by the program
 * @av:name of program
 *
 * Return: retuns 1 if command is found, 0 if not
 */
int handle_other(char **command, char *user_input, int exit_status,
		 char **env, char *av)
{
	int i;

	if (!_strcmp(command[0], "exit"))
		handle_exit(command, user_input, exit_status);
	if (!_strcmp(command[0], "env"))
	{
		handle_env(env);
		return (0);
	}
	for (i = 0; command[i] != NULL; i++)
	{
		if (!_strcmp(command[i], "$$") || !_strcmp(command[i], "$?"))
			command[i] = handle_replacement(command[i],
							exit_status);
	}
	if (!_strcmp(command[0], "echo"))
	{
		if (command[1] == NULL)
		{
			write(1, "\n", 1);
			return (0);
		}
		handle_echo(command, exit_status, env);
		return (0);
	}

	if (!_strcmp(command[0], "cd"))
	{
		change_dir(command, av);
		return (0);
	}
	return (-1);
}

/**
 * handle_echo - handles the default echo command
 * @command: array of tokenized user input
 * @exit_status: the exit status of the last process
 * @env: the environment variable from the program
 */
void handle_echo(char **command, int exit_status, char **env)
{
	char *path;
	int i;

	(void)exit_status; /* should remove the function param */
	for (i = 1; command[i] != NULL; i++)
	{
		if (i > 1)
			_puts(" ");
		if (!_strcmp(command[i], "$PATH"))
		{
			path = get_path(env);
			_puts(path);
			free(path);
			continue;
		}
		_puts(command[i]);
	}
	_puts("\n");
}

char *handle_replacement(char *command, int exit_status)
{
	pid_t pid = getpid();

	if (!_strcmp(command, "$$"))
	{
		_itoa(pid, pid_str, 10);
		return (pid_str);
	}
	if (!_strcmp(command, "$?"))
	{
		_itoa(exit_status, exit_str, 10);
		return (exit_str);
	}
	return (NULL);
}
