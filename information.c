#include "shell.h"

/**
 * infoClr - initializes info_t struct
 *
 * @info: struct address
 */
void infoClr(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * infoInit - initializes info_t struct
 *
 * @info: struct address
 *
 * @av: argument vector
 */
void infoInit(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strSplit(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strDup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * freeSF - Frees info_t struct fields
 *
 * @info: Struct address
 *
 * @all: True if freeing all fields
 */
void freeSF(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freelist(&(info->env));
		if (info->history)
			freelist(&(info->history));
		if (info->alias)
			freelist(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		freeNullPtr((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		putChar(BUF_FLUSH);
	}
}
