#include "shell.h"

/**
 * _err_atoi - comvert string to integer
 * @str: string to be converted
 *
 * Return: 0 or -1
 */
int _err_atoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _printError - print error message
 * @info: struct
 * @err_str: string containing error
 *
 * Return: 0 or -1
 */
void _printError(info_t *info, char *err_str)
{
	_errorPuts(info->fname);
	_errorPuts(": ");
	print_dec(info->l_count, STDERR_FILENO);
	_errorPuts(": ");
	_errorPuts(info->argv[0]);
	_errorPuts(": ");
	_errorPuts(err_str);
}

/**
 * print_dec - print a decimal
 * @input: the input
 * @fd: filedescriptor
 *
 * Return: number of character printed
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _errorPutchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * conv_num -converter function, clone of atio
 * @base: base
 * @number: the number
 * @flags: argument flags
 *
 * Return: string
 */
char *conv_num(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long num = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		num = -number;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[num % base];
		num /= base;
	} while (num != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comment - replace first instance of '#' with '\0'
 * @buf: address of string to modify
 *
 * Return: 0
 */
void remove_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{

			buf[i] = '\0';
			break;
		}
	}
}
