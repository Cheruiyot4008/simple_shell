#include "shell.h"

/**
 * _historylist - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0
 */
int _historylist(info_t *info)
{
	printLlist(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 *
 * @info: parameter struct
 *
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = strChr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deletenode_at_index(&(info->alias),
		nodeIndex(info->alias, prefixNode(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 *
 * @info: parameter struct
 *
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = strChr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (addnode_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 *
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strChr(node->str, '=');
		for (a = node->str; a <= p; a++)
			putChar(*a);
		putChar('\'');
		strPuts(p + 1);
		strPuts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 *
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strChr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(prefixNode(info->alias, info->argv[i], '='));
	}

	return (0);
}
