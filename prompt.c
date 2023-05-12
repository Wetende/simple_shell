#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * get_input - Prompts for input, reads the command,
 * and prints it on the next line.
 */

void get_input(void)
{
	write(STDOUT_FILENO, "$ ", 2);

	char ch;
	char command[256];
	int index = 0;

	while (read(STDIN_FILENO, &ch, 1) != -1)
	{
		command[index] = ch;

		if (ch == '\n')
			break;
		index++;
	}
	write(STDOUT_FILENO, command, index);
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * main - Entry point of the program
 *
 * Return: Always 0
 */
int main(void)
{
	get_input();
	return (0);
}
