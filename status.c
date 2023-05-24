#include "shell.h"
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
	int i;

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
	for (i = 0; i < len / 2; i++)
	{
		char tmp = buffer[i];

		buffer[i] = buffer[len - i - 1];
		buffer[len - i - 1] = tmp;
	}

	buffer[len] = '\n';

	write(STDOUT_FILENO, message, strlen(message));
	write(STDOUT_FILENO, buffer, len + 1);
}

