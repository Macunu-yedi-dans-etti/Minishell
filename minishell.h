#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "includes/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_OUT,     // >
	T_REDIR_IN,      // <
	T_REDIR_APPEND,  // >>
	T_REDIR_HEREDOC  // <<
}	t_token_type;

typedef struct s_cmd
{
    char    *cmd;         // Komutun kendisi (örneğin "ls")
    char    **args;       // Argümanlar (örneğin {"ls", "-la", NULL})
    char    *redir_in;    // < dosya
    char    *redir_out;   // > dosya
    char    *redir_append; // >> dosya
    char    *heredoc;     // << limiter
    struct s_cmd *next;   // pipe için bir sonraki komut
} t_cmd;

typedef struct s_token
{
	char			*value;         // token metni
	t_token_type	type;           // token tipi
	struct s_token	*next;          // bağlı liste yapısı
}	t_token;

void	*paths(char *cmd, char **env);

void	ft_free(char **arr);

void	ft_err(char *str);
void    ft_free_stacks(t_token **a_stack);

int		build_exit(char **args);

char	**copy_env(char **envp);
int		builtin_env(char **env);

char    **add_to_env(char **env, char *new_var);
int     command_export(char ***env, char **args);

char	**remove_from_env(char **env, const char *key);
int	command_unset(char ***env, char **args);

t_token	*lexer(const char *input);
//void	add_token(t_token **head, char *value, t_token_type type);
void	free_tokens(t_token *head);
//void	print_tokens(t_token *head);  // debug
t_cmd	*parser(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void free_input_token(t_token *cmds);

void exec_cmds(t_cmd *cmds, char ***env);

# endif
