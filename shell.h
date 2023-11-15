#ifndef _SHELL_H
#define _SHELL_H

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


#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024

#define BUFF_FLUSH -1

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2


#define USE_GETLINE 0
#define USE_STRTOK  0

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3


#define HIST_FILE ".simple_history"
#define HIST_MAX 4096

extern char **environ;
/**
 * struct liststring - linked list
 * @num: the number of field
 * @data: str to data
 * @next: point to the next node
 */
typedef struct liststring
{
	int num;
	char *data;
	struct liststring *next;
} list_t;

/**
 * struct info - enviroment info
 * @arg: arg
 * @argv: argv
 * @path:str path
 * @argc: arg count
 * @l_count: error count
 * @e_num: error for exit
 * @l_count_flag: line count
 * @fname: programm name
 * @env: linked list
 * @history: node history
 * @alias: alias node
 * @environ: envirment
 * @env_change: if enviroment changed
 * @status: the status
 * @cmd_buf: address of pointer to cmd_buf
 * @cmd_buf_type: CMD_type
 * @readfd: the fd
 * @history_count: the history count
 */
typedef struct info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int l_count;
	int e_num;
	int l_count_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_change;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int history_count;
} info_t;

#define INIT_INFO\
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
				0, 0, 0}

/**
 * struct builtin - pointer to function with corresponding build command
 * @type: build command
 * @func: execute the build command
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} built_table;

char *_strdup(const char *src);
char *_strcat(char *dest, char *src);
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *_startWith(const char *haystack, const char *needle);
int _putchar(char c);
void _puts(char *str);
char *_strcpy(char *dest, char *src);
char **get_env(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);
int _env(info_t *info);
char *_getenv(info_t *info, const char *name);
int _thesetenv(info_t *info);
int _theunsetenv(info_t *info);
int _pop_env_list(info_t *info);
int _err_atoi(char *str);
int print_dec(int input, int fd);
void _printError(info_t *info, char *err_str);
char *conv_num(long int number, int base, int flags);
void remove_comment(char *buf);
int _errorPutchar(char c);
void _errorPuts(char *str);
int _putcharfd(char c, int fd);
int _putsfd(char *str, int fd);
char *strn_cpy(char *dest, char *src, int n);
char *strn_cat(char *dest, char *src, int n);
char *_strchr(char *str, char c);
int _exit_(info_t *info);
void *_reallocat(void *ptr, unsigned int old_size, unsigned int new_size);
void _free(char **pp);
char *_memoryset(char *s, char b, unsigned int n);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t _pListstr(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
int free_p(void **ptr);
void free_l(list_t **head_ptr);
size_t l_len(const list_t *head);
char **list_to_str(list_t *head);
size_t _printList(const list_t *head);
list_t *node_startwith(list_t *node, char *pre, char c);
ssize_t get_n_index(list_t *head, list_t *node);
int hsh(info_t *info, char **av);
int findBuiltin(info_t *info);
void findCMD(info_t *info);
void forkCMD(info_t *info);
char **_strtok(char *str, char *d);
int _stringReplac(char **old, char *new);
int _varsReplac(info_t *info);
int _aliasReplac(info_t *info);
void _checkChain(info_t *info, char *buf, size_t *str, size_t i,
								 size_t length);
int _isChain(info_t *info, char *buf, size_t *str);
void clearInfo(info_t *info);
void setInfo(info_t *info, char **av);
void freeInfo(info_t *info, int all);
int isCMD(info_t *info, char *path);
int _isalpha(int c);
int _isdelim(char c, char *delim);
int _isInteractive(info_t *info);
int _alias(info_t *info);
int _printalias(list_t *node);
int _setalias(info_t *info, char *str);
int _unsetalias(info_t *info, char *str);
int _history(info_t *info);
int _help(info_t *info);
int _cd(info_t *info);
char *find_path(info_t *info, char *strpath, char *cmd);
int main(int argc, char **argv);
int _renumberHistory(info_t *info);
int _listHistory(info_t *info, char *buf, int lcount);
int _readHistory(info_t *info);
int _writeHistory(info_t *info);
char *_getHistory(info_t *info);
int _atoi(char *str);
ssize_t input_buff(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
int _getline(info_t *info, char **buff, size_t *len);
ssize_t read_buf(info_t *info, char *buf, size_t *size);
void sig_HAND(__attribute__((unused)) int sig_num);

#endif
