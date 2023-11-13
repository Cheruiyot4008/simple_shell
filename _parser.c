#include "shell.h"

/**
 * iscmd - determines if a file is an executable command
 * 
 * @info: the info struct
 * 
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int iscmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * 
 * @pathstr: the PATH string
 * 
 * @start: starting index
 * 
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int q, r = 0;

	for (q = start; q < stop; q++)
	{
		if (pathstr[q] != ':')
		{
			buf[r] = pathstr[q];
			r++;
		}
	}

	buf[r] = 0;
	return (buf);
}
/**
 * findpath - finds this cmd in the PATH string
 * 
 * @info: the info struct
 * 
 * @pathstr: the PATH string
 * 
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *findpath(info_t *info, char *pathstr, char *cmd)
{
	int q = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (iscmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[q] || pathstr[q] == ':')
		{
			path = dup_chars(pathstr, curr_pos, q);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (iscmd(info, path))
				return (path);
			if (!pathstr[q])
				break;
			curr_pos = q;
		}
		q++;
	}
	return (NULL);
}
