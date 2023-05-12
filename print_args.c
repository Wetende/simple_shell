#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * print_arguments - print all the arguments
 * @argc: the number of arguments
 * @argv: value of arguments
 */

void print_arguments(int argc, char **argv)
{
	int i;

	for (i = 1; i < argc; i++)
	{

		size_t arg_length = strlen(argv[i]);

		write(STDOUT_FILENO, argv[i], arg_length);
		write(STDOUT_FILENO, " ", 1);
	}


write(STDOUT_FILENO, "\n", 1);
}

/**
 * main - function entry
 * Return: always 0 success
 * @argc: the number of arguments
 * @argv: value of arguments
 */
int main(int argc, char **argv)
{
	print_arguments(argc, argv);
	return (0);
}

