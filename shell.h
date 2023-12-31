#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int iscmd(info_t *, char *);
char *dupchars(char *, int, int);
char *findpath(info_t *, char *, char *);


int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);


char *strCpy(char *, char *);
char *strDup(const char *);
void strPuts(char *);
int putChar(char);


char *strnCpy(char *, char *, int);
char *strnConcat(char *, char *, int);
char *strChr(char *, char);


int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);


char **strSplit(char *, char *);
char **strSplit2(char *, char);


char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);


int freeNullPtr(void **);

int loophsh(char **);

int interact(info_t *);
int isDelim(char, char *);
int isAlpha(int);
int _atoi(char *);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


int str_int(char *);
void printError(info_t *, char *);
int decPrint(int, int);
char *numConverter(long int, int, int);
void clrComments(char *);


int shellExit(info_t *);
int cdChange(info_t *);
int proCdCh(info_t *);


int _historylist(info_t *);
int _myalias(info_t *);


ssize_t getinput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);


void infoClr(info_t *);
void infoInit(info_t *, char **);
void freeSF(info_t *, int);


char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);


char *fetchHist(info_t *info);
int crepend(info_t *info);
int histRec(info_t *info);
int buildLlist(info_t *info, char *buf, int linecount);
int updateLlistNum(info_t *info);


list_t *addnode(list_t **, const char *, int);
list_t *addnode_end(list_t **, const char *, int);
size_t printlist_str(const list_t *);
int deletenode_at_index(list_t **, unsigned int);
void freelist(list_t **);


size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t printLlist(const list_t *);
list_t *prefixNode(list_t *, char *, char);
ssize_t nodeIndex(list_t *, list_t *);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int is_chain(info_t *, char *, size_t *);
int _myunsetenv(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int populate_env_list(info_t *);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
