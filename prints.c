#include "pshell.h"
#include <unistd.h>
#include <limits.h>

/**
 * print_integer - prints integers
 * @num: number
 * Return: lenght of integer
 */

int print_integer(int num)
{
	int len = 0;

	if (num == (INT_MIN))
		return (_puts("-2147483648", STDERR_FILENO));
	if (num < 0)
	{
		len += _putchar('-');
		num = -num;
	}

	if (num >= 10)
	{
		len += (print_integer(num / 10));
	}
	_putchar(num % 10 + '0');
	len++;
	return (len);
}

/**
 * _puts - prints a string to file
 * @str: string
 * @fd: file descriptor
 * Return: number of character printed
 */

int _puts(char *str, int fd)
{
	int l = 0;

	if (str == NULL)
		str = "(null)";
	if (*str == '\0')
		return (0);
	l = write(fd, str, _strlen(str));
	return (l);
}


/**
 * _putchar - writes character c to stdout
 * Return: 1 on success.
 * @c: character to print
 *
 * -1 on error. errno is set approximately
 */
int _putchar(char c)
{
	return (write(STDERR_FILENO, &c, 1));
}

/**
 * printMsg - prints error message
 * @command_no: command id
 * @program_name: executable name
 * @command: command entered
 * @error_: error message
 */
void printMsg(int command_no, char *program_name, char *command, char *error_)
{
	_puts(program_name, STDERR_FILENO);
	_puts(": ", STDERR_FILENO);
	print_integer(command_no);
	_puts(": ", STDERR_FILENO);
	_puts(command, STDERR_FILENO);
	_puts(": ", STDERR_FILENO);
	_puts(error_, STDERR_FILENO);
}
