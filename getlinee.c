#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @infos: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(infos_t *infos, char **buf, size_t *len)
{
	ssize_t g = 0;
	size_t len_m = 0;

	if (!len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)infos->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		g = getline(buf, &len_m, stdin);
#else
		g = _getline(infos, buf, &len_m);
#endif
		if (g > 0)
		{
			if ((*buf)[g - 1] == '\n')
			{
				(buf)[g - 1] = '\0'; /* remove trailing newline */
				g--;
			}
			infos->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(infos, *buf, infos->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = g;
				infos->cmd_buf = buf;
			}
		}
	}
	return (g);
}

/**
 * get_input - gets a line minus the newline
 * @infos: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(infos_t *infos)
{
	static char buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t g = 0;
	char **buf_m = &(infos->arg), *m;

	_putchar(BUF_FLUSH);
	g = input_buf(infos, &buf, &len);
	if (g == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		m = buf + i; /* get pointer for return */

		check_chain(infos, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(infos, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			infos->cmd_buf_type = CMD_NORM;
		}

		buf_m = m; /* pass back pointer to current command position */
		return (_strlen(m)); /* return length of current command */
	}

	buf_m = buf; /* else not a chain, pass back buffer from _getline() */
	return (g); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @infos: parameter struct
 * @buf: buffer
 * @h: size
 *
 * Return: g
 */
ssize_t read_buf(info_t *infos, char *buf, size_t *h)
{
	ssize_t g = 0;

	if (*h)
		return (0);
	g = read(infos->readfd, buf, READ_BUF_SIZE);
	if (g >= 0)
		*h = g;
	return (g);
}

/**
 * _getline - gets the next line of input from STDIN
 * @infos: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: l
 */
int _getline(infos_t *infos, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t g = 0, l = 0;
	char *m = NULL, *new_m = NULL, *c;

	m = *ptr;
	if (m && length)
		l = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(infos, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	v = _strchr(buf + i, '\n');
	k = v ? 1 + (unsigned int)(v - buf) : len;
	new_m = _realloc(m, l, l ? l + k : k + 1);
	if (!new_m) /* MALLOC FAILURE! */
		return (m ? free(p), -1 : -1);

	if (l)
		_strncat(new_m, buf + i, k - i);
	else
		_strncpy(new_m, buf + i, k - i + 1);

	l += k - i;
	i = k;
	m = new_m;

	if (length)
		*length = l;
	*ptr = m;
	return (l);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: The number representing the signal.
 *
 * Return: void
 */
void sigintHandler(_attribute_((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

