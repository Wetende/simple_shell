#include "shell.h"
/**
 * write_status_message - Write a status message to standard output.
 * @message: The message to be written.
 * @status: The status value to be displayed.
 */
void write_status_message(const char *message, int status)
{
    char buffer[BUFSIZE];
    int len = 0;
    int temp = status;

    if (temp < 0)
    {
        buffer[len++] = '-'; /* Add a '-' sign for negative numbers */
        temp = -temp;
    }
    else if (temp == 0)
    {
        buffer[len++] = '0'; /* Handle case when status is 0 */
    }

    /* Convert the status value to string representation */
    while (temp != 0)
    {
        buffer[len++] = '0' + (temp % 10);
        temp /= 10;
    }

    if (status < 0)
    {
        buffer[len++] = '-'; /* Add a '-' sign for negative numbers */
    }

    /* Reverse the order of the digits in the buffer */
    for (int i = 0; i < len / 2; i++)
    {
        char tmp = buffer[i];
        buffer[i] = buffer[len - i - 1];
        buffer[len - i - 1] = tmp;
    }

    buffer[len] = '\n'; /* Add a newline character at the end of the buffer */

    /* Write the message and the buffer to standard output */
    write(STDOUT_FILENO, message, strlen(message));
    write(STDOUT_FILENO, buffer, len + 1);
}

