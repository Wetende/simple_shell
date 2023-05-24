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
	int (*func)(data *);
} builtin_table;


/* toem_shloop.c */
int hsh(data *, char **);
int get_builtin(data *);
void get_command(data *);
void forkCommand(data *);

/* toem_parser.c */
int is_command(data *, char *);
char *duplicate_chars(char *, int, int);
char *search_path(data *, char *, char *);

/* loop_hsh.c */
int loop_hsh(char **);

/* toem_errors.c */
void eputs_me(char *);
int eputchar_me(char);
int putfd_me(char c, int fd);
int putsfd_me(char *str, int fd);

/* toem_string.c */
int my_strlen(char *);
int my_strcmp(char *, char *);
char *_beginWith(const char *, const char *);
char *my_strcat(char *, char *);

/* toem_string1.c */
char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void _puts(char *);
int my_putchar(char);

/* toemexit_mes.c */
char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **my_strtow2(char *, char);

/* toemmy_realloc.c */
char *my_memset(char *, char, unsigned int);
void ffree(char **);
void *my_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int buff_free(void **);

/* toem_atoi.c */
int responsive(data *);
int delimeter_me(char, char *);
int isalpha_me(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void _myerror_printing(data *, char *);
int _myprint(int, int);
char *num_conversion(long int, int, int);
void rm_comments(char *);

/* toem_builtin.c */
int exit_me(data *);
int cd_me(data *);
int help_me(data *);

/* toem_builtin1.c */
int history_me(data *);
int alias_me(data *);

/*toem_getline.c */
ssize_t read_input(data *);
int _getline(data *, char **, size_t *);
void handle_sigint(int);

/* toem_getinfo.c */
void deleteInformation(data *);
void setInformation(data *, char **);
void freeInformation(data *, int);

/* toem_environ.c */
char *_getenv(data *, const char *);
int _myenv(data *);
int _mysetenv(data *);
int _myunsetenv(data *);
int increase_env_list(data *);

/* toem_getenv.c */
char **take_environ(data *);
int _unsetenv(data *, char *);
int _setenv(data *, char *, char *);

/* toem_history.c */
char *take_hist_file(data *info);
int put_hist(data *info);
int look_into_hist(data *info);
int create_hist_list(data *info, char *buf, int linecount);
int number_again_hist(data *info);

/* toem_lists.c */
list_t *insert_node(list_t **, const char *, int);
list_t *insert_end_node(list_t **, const char *, int);
size_t list_printed_string(const list_t *);
int del_node_index(list_t **, unsigned int);
void _freeList(list_t **);

/* toem_lists1.c */
size_t listLength(const list_t *);
char **list_str(list_t *);
size_t list_is_print(const list_t *);
list_t *begin_node_with(list_t *, char *, char);
ssize_t take_index_node(list_t *, list_t *);

/* toem_vars.c */
int the_chain(data *, char *, size_t *);
void _checkChain(data *, char *, size_t *, size_t, size_t);
int _replaceAlias(data *);
int replace_variable(data *);
int replace_str(char **, char *);

#endif
