#include "shell.h"
/**
 *input_buff - buffers chained
 * @info: strcut param
 * @buf: buff address
 * @len: length var address
 *
 * Return: byte_read
 */
ssize_t input_buff(info_t *info, char **buf, size_t *len)
{
	ssize_t byte_read = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sig_HAND);
#if USE_GETLINE
		byte_read = getline(buf, &len_p, stdin);
#else
		byte_read = _getline(info, buf, &len_p);
#endif
		if (byte_read > 0)
		{
			if ((*buf)[byte_read - 1] == '\n')
			{
				(*buf)[byte_read - 1] = '\0';
				byte_read--;
			}
			info->l_count_flag = 1;
			remove_comment(*buf);
			_listHistory(info, *buf, info->history_count++);
			if (_strchr(*buf, ';'))
			{
				*len = byte_read;
				info->cmd_buf = buf;
			}
		}
	}
	return (byte_read);
}

/**
 * get_input - gets a line minus the newline
 * @info: stract param
 *
 * Return: byte_read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t byte_read = 0;
	char **buf_p = &(info->arg), *ptr;

	_putchar(BUFF_FLUSH);
	byte_read = input_buff(info, &buf, &len);
	if (byte_read == -1)
		return (-1);
	if (len)
	{
		j = i;
		ptr = buf + i;

		_checkChain(info, buf, &j, i, len);
		while (j < len)
		{
			if (_isChain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = ptr;
		return (_strlen(ptr));
	}
	*buf_p = buf;
	return (byte_read);
}

/**
 * read_buf - reads buff
 * @info: strct param
 * @buf: buffer address
 * @size: size of read
 *
 * Return: byte_read
 */
ssize_t read_buf(info_t *info, char *buf, size_t *size)
{
	ssize_t byte_read = 0;

	if (*size)
		return (0);
	byte_read = read(info->readfd, buf, READ_BUFF_SIZE);
	if (byte_read >= 0)
		*size = byte_read;
	return (byte_read);
}

/**
 * _getline - gets next line of input from stdin
 * @info: struct
 * @buff: addrees of pointer to buffer
 * @len: size of buffer
 *
 * Return: s
 */
int _getline(info_t *info, char **buff, size_t *len)
{
	static char buf[READ_BUFF_SIZE];
	static size_t i, _len;
	size_t j;
	ssize_t byte_read = 0, s = 0;
	char *ptr = NULL, *new_ptr = NULL, *c;

	ptr = *buff;
	if (ptr && len)
		s = *len;
	if (i == _len)
		i = _len = 0;

	byte_read = read_buf(info, buf, &_len);
	if (byte_read == -1 || (byte_read == 0 && _len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : _len;
	new_ptr = _reallocat(ptr, s, s ? s + j : j + 1);
	if (!new_ptr)
		return (ptr ? free(ptr), -1 : -1);
	if (s)
		strn_cat(new_ptr, buf + i, j - i);
	else
		strn_cpy(new_ptr, buf + i, j - i + 1);

	s += j - i;
	i = j;
	ptr = new_ptr;

	if (len)
		*len = s;
	*buff = ptr;
	return (s);
}

/**
 * sig_HAND - ctrl-c
 * @sig_num: signal number;
 *
 * Return: void
 */
void sig_HAND(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
