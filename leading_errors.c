#include "shell.h"
#include <unistd.h>
/**
 * _eputs - prints an input string
 *
 * @str: the string to be printed
 *
 * Return: Nothing
 */
	void _eputs(char *str)
	{
	int b = 0;

	if (!str)
	return;
	while (str[b] != '\0')
	{
	_eputchar(str[b]);
	b++;
	}
	}
/**
 * _eputchar - writes the character c to stderr
 *
 * @c: The character to print
 *
 * Return: On success 1.
 *
 * On error, -1 is returned, and errno is set appropriately.
 */
	int _eputchar(char c)
	{
	static int b;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
	write(2, buf, b);
	 b = 0;
	}
	if (c != BUF_FLUSH)
	buf[b++] = c;
	return (1);
	}
/**
 * _putfd - writes the character c to given fd
 *
 * @c: The character to print
 *
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 *
 * On error, -1 is returned, and errno is set appropriately.
 */
	int _putfd(char c, int fd)
	{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
	write(fd, buf, a);
	a = 0;
	}
	if (c != BUF_FLUSH)
	buf[a++] = c;
	return (1);
	}
/**
 * _putsfd - Prints an input string
 *
 * @str: The string to be printed
 *
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters put
 */
	int _putsfd(char *str, int fd)
	{
	int a = 0;

	if (!str)
	return (0);
	while (*str)
	{
	a += _putfd(*str, fd);
	str++;
	}
	return (a);
	}
