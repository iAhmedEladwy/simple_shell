#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 => success | 1 => error
 */

int main(int argc, char **argv)
{
	info_t info[] = {INIT_INFO};
	int fd = 2;

	asm("mov %1, %0\n\t"
			"add $3, %0"
			: "=r"(fd)
			: "r"(fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errorPuts(argv[0]);
				_errorPuts(": 0: Can't Open");
				_errorPuts(argv[1]);
				_errorPutchar('\n');
				_errorPutchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	else if (argc == 1 && isatty(STDIN_FILENO) == 0)
	{
		info->readfd = STDIN_FILENO;
	}
	_pop_env_list(info);
	_readHistory(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
