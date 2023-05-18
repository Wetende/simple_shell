#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>

#define BUFSIZE 1024
#define PROMPT "$ "
/**
 * get_command - function that gets commands from stdin and generates output
 * @cmd: commands to get
 */
void get_command(char **cmd)
{
	write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
	fflush(stdout);
	*cmd = NULL;
	size_t bufsize = 0;

	if (getline(cmd, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * write_status_message - function that checks for the status of input and
 * writes a status message accordingly
 * @message: the message to be printed
 * @status: the values to be displayed
 */
void write_status_message(const char *message, int status)
{
	char buffer[BUFSIZE];
	int len = 0;
	int temp = status;

	if (temp < 0)
	{
		buffer[len++] = '-';
		temp = -temp;
	}
	else if (temp == 0)
	{
		buffer[len++] = '0';
	}
	while (temp != 0)
	{
		buffer[len++] = '0' + (temp % 10);
		temp /= 10;
	}
	if (status < 0)
	{
		buffer[len++] = '-';
	}
	for (int i = 0; i < len / 2; i++)
	{
		char tmp = buffer[i];

		buffer[i] = buffer[len - i - 1];
		buffer[len - i - 1] = tmp;
	}

	buffer[len] = '\n';

	write(STDOUT_FILENO, message, strlen(message));
	write(STDOUT_FILENO, buffer, len + 1);
}

/**
 * execute_command - function that takes in commands from stdin and
 * executes them.
 * @cmd: commands to take in
 */
void execute_command(char *cmd)
{
	char *args[BUFSIZE];
	int argc = 0;
	char *token;

	token = strtok(cmd, " \t\n");
	while (token != NULL)
	{
		args[argc++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[argc] = NULL;
	if (strcmp(args[0], "exit") == 0)
	{
		exit(0);
	}
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0)
	{
		execvp(args[0], args);
		perror(args[0]);
		exit(EXIT_FAILURE);
	} else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			write_status_message("Child exited with status ", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			write_status_message("Child killed by signal ", WTERMSIG(status));
		}
	}
}

/**
 * main - Entry point
 * Return: 0 on success
 */
int main(void)
{
	char *cmd = NULL;

	while (1)
	{
		get_command(&cmd);
		execute_command(cmd);
	}

	free(cmd);

	return (0);
}
