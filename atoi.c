#include "shell.h"

/**
 * _atoi - convert string to integer
 * @str: string to be converted
 *
 * Return: 0 or converted number
 */
int _atoi(char *str)
{
	int i, mark = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			mark *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (mark == -1)
		output = -result;
	else
		output = result;

	return (output);
}
