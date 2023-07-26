#include "shell.h"

/**
 * get_history_file - generates the full path of the history file
 *
 * @infos: contains environment variable data
 * Return: dynamically allocated string containing
 * the path to the history file, or NULL
 */
char *get_history_file(infos_t *infos)
{
	char *buf, *dir;

	dir = _getenv(infos, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - writes contents of the commabd history
 *
 * @infos: contains command history data
 * Return: 1 on success, -1 on failure
 */
int write_history(infos_t *infos)
{
	ssize_t fd;
	char *filename = get_history_file(infos);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = infos->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads the command from history file
 *
 * @infos: stores the command history data
 * Return: histcount on success, 0 otherwise
 */
int read_history(infos_t *infos)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(infos);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(infos, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(infos, buf + last, linecount++);
	free(buf);
	infos->histcount = linecount;
	while (infos->histcount-- >= HIST_MAX)
		delete_node_at_index(&(infos->history), 0);
	renumber_history(infos);
	return (infos->histcount);
}

/**
 * build_history_list - Adds a new command history entry to the history list
 *
 * @infos: containing the command history entry
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always returns 0
 */
int build_history_list(infos_t *infos, char *buf, int linecount)
{
	list_t *node = NULL;

	if (infos->history)
		node = infos->history;
	add_node_end(&node, buf, linecount);
	if (!infos->history)
		infos->history = node;
	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 *
 * @infos: Structure containing the command history data.
 * Return: returns the new histcount
 */
int renumber_history(infos_t *infos)
{
	list_t *node = infos->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (infos->histcount = i);
}
