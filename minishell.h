#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include "includes/mini_error.h"
#include "includes/libft/libft.h"
#include "includes/color.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <errno.h>

typedef struct s_request
{
    t_list *cmds;
    char **envp;
    pid_t pid;
    int exit_stat;
} t_req;

typedef enum e_redirect_type
{
    R_IN,    // <
    R_OUT,   // >
    R_APPEND // >>
} t_redirect_type;

typedef struct s_redirect
{
    char *filename;
    t_redirect_type type;
    struct s_redirect *next;
} t_redirect;

typedef struct s_shell
{
    char **full_cmd; // {"ls", "-l", NULL}
    char *full_path; // /bin/ls
    int infile;
    int outfile;
    char *infile_path;
    char *outfile_path;
    int append_out;
    t_redirect *redirects; // new: list of all redirects for this command
} t_shell;

typedef enum e_quote_type
{
    QUOTE_NONE,
    QUOTE_SINGLE,
    QUOTE_DOUBLE
} t_quote_type;

typedef struct s_token
{
    char *str;
    t_quote_type quote;
} t_token;

// exit
extern int g_exit_status;

// enviroment
char **mini_setenv(char *var, char *value, char **envp, int n);
char *mini_getenv(char *var, char **envp, int n);
char **mini_unsetenv(char ***envp, const char *var);

// mini_setenv_line
char **mini_setenv_line(char ***envp, const char *line);

// utility
int ft_find_chr(const char *s, char c);
char **ft_double_extension(char **matrix, char *new_str);
char **ft_double_copy(char **envp);
t_list *ft_lstnew(void *content);
void ft_lstadd_back(t_list **lst, t_list *new_node);
void strip_newline(char *s);

// resolve_path
char *resolve_path(char *cmd, char **envp);

// ft_free
void ft_free(char **tab);
void ft_double_free(char ***freee);
void free_cmds(t_list *cmds);
void free_all(t_req *req);
void free_tokens(t_token **tokens); // YENİ
void free_redirects(t_redirect *redir);

// signal
void handle_sigint(int sig);
void handle_sigquit(int sig);
void setup_signals(void);
void reset_signals(void);

// input_message
char *mini_getinput(t_req input);

// tokenizer
t_token **tokenize_input(const char *input);

// parser
t_list *parse_tokens(t_token **tokens, t_req *req);

// expander
char *expand_str(const char *input, char **envp, int quote);
// executor
void execute_cmds(t_list *cmds, t_req *req);

// builtin
int run_builtin(t_shell *cmd, t_req *req);
int is_builtin(char *cmd);
int builtin_echo(t_shell *cmd); // echo
int builtin_pwd(void);          // pwd
int builtin_env(char **envp);   // env
int builtin_cd(t_shell *cmd, t_req *req);
int builtin_export(char **args, t_req *req);
int builtin_unset(char **args, t_req *req);
int builtin_exit(char **args);

// cd utils
void print_cd_error(char *arg, char *msg);
char *get_cd_target(t_shell *cmd, t_req *req, int *need_free);

// redirect
int apply_redirects(t_shell *cmd);

// heredoc
int handle_heredoc(const char *delimiter);

#endif