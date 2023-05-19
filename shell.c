#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void writeToStdout(const char *message)
{
	write(STDOUT_FILENO, message, strlen(message));
}

void executeCommand(const char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execl(command, command, (char *)NULL);
		perror("exec");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			char exitStatusMessage[50];
			sprintf(exitStatusMessage, "Command exited with status: %d\n", WEXITSTATUS(status));
			writeToStdout(exitStatusMessage);
		}
		else
		{
			writeToStdout("Command did not exit normally\n");
		}
	}
}

int main()
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		writeToStdout("#cisfun$ ");
		
		ssize_t bytesRead = read(STDIN_FILENO, command, sizeof(command));
		if (bytesRead == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0)
		{
			break;
		}

		executeCommand(command);
	}

	return 0;
}
