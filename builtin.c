#include "shell.h"

/**
 * exit_me - exits shell
 * @args: Structure for arguments
 *  Return:  exit status
 */
int exit_me(data *args)
{
	int exitcheck;

	if (args->argv[1])  
	{
		exitcheck = _erratoi(args->argv[1]);
		if (exitcheck == -1)
		{
			args->status = 2;
			_myerror_printing(args, "Illegal number: ");
			eputs_me(args->argv[1]);
			eputchar_me('\n');
			return (1);
		}
		args->err_num = _erratoi(args->argv[1]);
		return (-2);
	}
	args->err_num = -1;
	return (-2);
}

/**
 * help_me - change current process directory
 * @args: arguments to be used
 *  Return: Return Always 0
 */
int help_me(data *args)
{
	char **arg_array;

	arg_array = args->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* unused array */
	return (0);
}


/**
 * cd_me - change  directory process
 * @args:  arguments
 *  Return: Returns Always 0
 */
int cd_me(data *args)
{
	char *string, *dir, buffer[1024];
	int chdir_ret;

	string = getcwd(buffer, 1024);
	if (!string)
		_puts("TODO: >>getcwd failure message here<<\n");
	if (!args->argv[1])
	{
		dir = _getenv(args, "HOME=");
		if (!dir)
			chdir_ret = /* what is this? */
				chdir((dir = _getenv(args, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (my_strcmp(args->argv[1], "-") == 0)
	{
		if (!_getenv(args, "OLDPWD="))
		{
			_puts(string);
			my_putchar('\n');
			return (1);
		}
		_puts(_getenv(args, "OLDPWD=")), my_putchar('\n');
		chdir_ret = /* Assignement: what is this this be? */
			chdir((dir = _getenv(args, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(args->argv[1]);
	if (chdir_ret == -1)
	{
		_myerror_printing(args, "can't cd to ");
		eputs_me(args->argv[1]), eputchar_me('\n');
	}
	else
	{
		_setenv(args, "OLDPWD", _getenv(args, "PWD="));
		_setenv(args, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

