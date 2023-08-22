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
 * switch_format - switches format
 * @c: character
 * @format_args: obviously
 * @fd: file descriptor
 * Return: int
 */

int switch_format(char c, va_list format_args, int fd)
{
	switch (c)
	{
		case 'c':
			return (_putchar(va_arg(format_args, int)));
		case 's':
			return (_puts(va_arg(format_args, char *), fd));
		case '%':
			return (_putchar(c));
		case 'd':
			return (print_integer(va_arg(format_args, int)));
		default:
			return (0);
	}
}
/**
 * _dprintf - prints format to stderr
 * @format: format string
 * @fd: file descriptor
 * Return: number characters printed
 */

int _dprintf(int fd, const char *format, ...)
{
	int len = 0, result;
	va_list format_args;

	va_start(format_args, format);
	if (format == NULL)
		return (-1);
	while (*format)
	{
		if (format[0] == '%' && *(format + 1) == '\0')
			return (-1);
		if (*format == '%')
		{
			format++;
			result = switch_format(*format, format_args, fd);
			if (result == -1)
				return (-1);
			len += result;
		}
		else
			len += _putchar(*format);
		format++;
	}
	va_end(format_args);
	return (len);
}

/**
 * printMsg - prints leading error message
 * @command_no: command id
 * @program_name: executable name
 */
void printMsg(int command_no, char *program_name)
{
	_puts(program_name, STDERR_FILENO);
	_puts(": ", STDERR_FILENO);
	print_integer(command_no);
	_puts(": ", STDERR_FILENO);
}
