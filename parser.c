#include "minishell.h"

static int count_args(t_token *tokens)
{
	int count = 0;
	while (tokens && tokens->type == T_WORD)
	{
		count++;
		tokens = tokens->next;
	}
	return count;
}

static char **collect_args(t_token **tokens)
{
	int i = 0;
	int size = count_args(*tokens);
	char **args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return NULL;
	while (*tokens && (*tokens)->type == T_WORD)
	{
		args[i++] = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return args;
}

t_cmd *parser(t_token *tokens)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return NULL;

	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->redir_append = NULL;
	cmd->heredoc = NULL;
	cmd->next = NULL;

	cmd->args = collect_args(&tokens);
	if (cmd->args && cmd->args[0])
		cmd->cmd = ft_strdup(cmd->args[0]); // ilk kelimeyi komut olarak al

	while (tokens)
	{
		if (tokens->type == T_REDIR_IN && tokens->next)
		{
			cmd->redir_in = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == T_REDIR_OUT && tokens->next)
		{
			cmd->redir_out = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == T_REDIR_APPEND && tokens->next)
		{
			cmd->redir_append = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == T_REDIR_HEREDOC && tokens->next)
		{
			cmd->heredoc = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == T_PIPE)
		{
			tokens = tokens->next;
			cmd->next = parser(tokens);
			break;
		}
		tokens = tokens->next;
	}

	return cmd;
}

