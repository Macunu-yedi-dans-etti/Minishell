#include "minishell.h"

static int	count_args(t_token *tokens)
{
	int	count = 0;
	while (tokens && tokens->type == T_WORD)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

static char	**collect_args(t_token **tokens)
{
	int		i = 0;
	int		size = count_args(*tokens);
	char	**args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	while (*tokens && (*tokens)->type == T_WORD)
	{
		args[i++] = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return (args);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->next = NULL;

	cmd->args = collect_args(&tokens);

	while (tokens)
	{
		if (tokens->type == T_REDIR_IN && tokens->next)
		{
			cmd->infile = ft_strdup(tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == T_REDIR_OUT && tokens->next)
		{
			cmd->outfile = ft_strdup(tokens->next->value);
			cmd->append = 0;
			tokens = tokens->next;
		}
		else if (tokens->type == T_REDIR_APPEND && tokens->next)
		{
			cmd->outfile = ft_strdup(tokens->next->value);
			cmd->append = 1;
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
	return (cmd);
}

