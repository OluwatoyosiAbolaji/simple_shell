#ifndef SHELL_H
#define SHELL_H

/* Header files */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>

/* MACROS */
#define BUFF_MAX 10240
#define INT_MAXI 10000000000
#define BUFSIZE 1024
#define ENOSTRING 1106
#define EILLEGAL 227
#define EWSIZE 410
#define ENOBUILTIN 415
#define EBADCD 726
/**
  *struct list - linked list of environmental variables
  *@string: string containing varible
  *@next: pointer to the next string
  */
typedef struct list
{
	char *string;
	struct list *next;
} list;

/**
  *struct shell - contains all information about shell session
  *@env_list: linked list of local env variables
 * @env_strings: array of env variables to put into execve
 * @args: array of argument strings
 * @buffer: string buffer of user input
 * @pathway: array of $PATH locations
 * @full_path: string of path with $PATH
 * @name: name of shell
 * @linecount: counter of lines users have entered
 * @status: exit status of last child process
 */
typedef struct shell
{
	list *env_list;
	char **env_strings;
	char **args;
	char *buffer;
	char *pathway;
	char *full_path;
	char *name;
	int linecount;
	int status;
} shell;

/* String aid functions */
int length(char *string);
char *duplicate(char *string);
char *copy(char *dest, char *src);
void setnull(char *string, int index);
char *char_locate(char a, char *string);
int index_locate(char *search, char *check);
char *tokenize(char *string, char *delim);
char *catenate(char *begin, char *end);
int compare(char *a, char *b);
int split(shell *session);

/* linked list aid functions */
list *addnode(list **head, char *string);
list *addendnode(list **head, char *string);
int node_search_index(list *head, char *string);
int nodesprint(list *head);
size_t listlength(list *head);
list *create_list(char **env);
list *nodeatindex(list **list, int index, char *string);
int delete_node(list **head, int index);
char *getNodeAtIndex(list *head, int index);

/* storage functions */
char *reallocate(char *ptr, size_t size, size_t newsize);
int _isalpha(int c);
void exitfunc(int a);

/* builtin functions */
int findbuiltin(shell *session);
int exitf(shell *session);
int cd(shell *session);
int cdhome(shell *session);
int cdprevious(shell *session);
int cdcustom(shell *session);
int updateEnviron(shell *session);
int updateprev(shell *session);
int updatenext(shell *session);
int env(shell *session);
int setenvFunc(shell *session);
int unsetenvFunc(shell *session);
/**
  *struct builtin - handles builtin functions
  *@string: string containing name of command
  *@func: function pointer of associated string
  */
typedef struct builtin
{
	char *string;
	int (*func)(shell *session);
} builtin;

/* shell functions */
void initialize_shell(shell *ptr, char **environ);
void delete_comment(char *string);
void get_input(shell *session);
void execute_shell(shell *session);
char *_getenv(char *input, char **environ);
void convert_list_to_arr(shell *session);
int set_home(shell *session);
void new_process(shell *session);
void printprompt(void);
void printline(void);
void check_path(shell *session);

/* free functions */
void freeall(shell *session);
void freeargbuffer(shell *session);
void freelist(list *head);
void freeargs(char **args);

/* Other helping functions */
int _atoi(char *s);
int countargs(char **args);
void signalhandle(int);
ssize_t _getline(char **lineptr, size_t *n, FILE *ptr);

/* Error Handling */
void errorHandler(shell *session);
char *getErrorMessage(void);
unsigned int countDigits(int num);
char *itoa(unsigned int num);

#endif /* SHELL_H */
