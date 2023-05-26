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

/* for num_conversion() */
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
} data_t;

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
	int (*func)(data_t *);
} builtin_table;


/* -shloop.c */
int hsh(data_t *, char **);
int get_builtin(data_t *);
void get_command(data_t *);
void forkCommand(data_t *);

/* -parser.c */
int is_command(data_t *, char *);
char *duplicate_chars(char *, int, int);
char *search_path(data_t *, char *, char *);

/* loop_hsh.c */
int loop_hsh(char **);

/* -errors.c */
void eputs_me(char *);
int eputchar_me(char);
int putfd_me(char c, int fd);
int putsfd_me(char *str, int fd);

/* -string.c */
int my_strlen(char *);
int my_strcmp(char *, char *);
char *_beginWith(const char *, const char *);
char *my_strcat(char *, char *);

/* -string1.c */
char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void _puts(char *);
int my_putchar(char);

/* -exit_mes.c */
char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

/* -tokenizer.c */
char **strtow(char *, char *);
char **my_strtow2(char *, char);

/* -my_realloc.c */
char *my_memset(char *, char, unsigned int);
void ffree(char **);
void *my_realloc(void *, unsigned int, unsigned int);

/* -memory.c */
int buff_free(void **);

/* -atoi.c */
int responsive(data_t *);
int delimeter_me(char, char *);
int isalpha_me(int);
int _atoi(char *);

/* -errors1.c */
int _erratoi(char *);
void _myerror_printing(data_t *, char *);
int _myprint(int, int);
char *num_conversion(long int, int, int);
void rm_comments(char *);

/* -builtin.c */
int exit_me(data_t *);
int cd_me(data_t *);
int help_me(data_t *);

/* -builtin1.c */
int history_me(data_t *);
int alias_me(data_t *);

/*-getline.c */
ssize_t read_input(data_t *);
int _getline(data_t *, char **, size_t *);
void handle_sigint(int);

/* -getinfo.c */
void deleteInformation(data_t *);
void setInformation(data_t *, char **);
void freeInformation(data_t *, int);

/* -environ.c */
char *_getenv(data_t *, const char *);
int _myenv(data_t *);
int _mysetenv(data_t *);
int _myunsetenv(data_t *);
int increase_env_list(data_t *);

/* -getenv.c */
char **take_environ(data_t *);
int _unsetenv(data_t *, char *);
int _setenv(data_t *, char *, char *);

/* -history.c */
char *take_hist_file(data_t *info);
int put_hist(data_t *info);
int look_into_hist(data_t *info);
int create_hist_list(data_t *info, char *buf, int linecount);
int number_again_hist(data_t *info);

/* -lists.c */
list_t *insert_node(list_t **, const char *, int);
list_t *insert_end_node(list_t **, const char *, int);
size_t list_printed_string(const list_t *);
int del_node_index(list_t **, unsigned int);
void _freeList(list_t **);

/* -lists1.c */
size_t listLength(const list_t *);
char **list_str(list_t *);
size_t list_is_print(const list_t *);
list_t *begin_node_with(list_t *, char *, char);
ssize_t take_index_node(list_t *, list_t *);

/* -vars.c */
int the_chain(data_t *, char *, size_t *);
void _checkChain(data_t *, char *, size_t *, size_t, size_t);
int _replaceAlias(data_t *);
int replace_variable(data_t *);
int replace_str(char **, char *);

#endif
