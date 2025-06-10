#include "../../minishell.h"

static t_shell *init_cmd(void)
{
	t_shell *cmd = malloc(sizeof(t_shell));
	if (!cmd)
		return (NULL);
	cmd->full_cmd = NULL;
	cmd->full_path = NULL;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->infile_path = NULL;
	cmd->outfile_path = NULL;
	cmd->append_out = 0;
	return (cmd);
}

static int is_redirect(char *token)
{
	return (!ft_strncmp(token, "<", 2) || !ft_strncmp(token, ">", 2) ||
		!ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3));
}

static int set_redirection(t_shell *cmd, char **tokens, int *i)
{
	char *redir = tokens[*i];
	(*i)++;
	if (!tokens[*i])
		return (1);
	if (!ft_strncmp(redir, "<", 2))
		cmd->infile_path = ft_strdup(tokens[*i]);
	else if (!ft_strncmp(redir, ">", 2))
	{
		cmd->outfile_path = ft_strdup(tokens[*i]);
		cmd->append_out = 0;
	}
	else if (!ft_strncmp(redir, ">>", 3))
	{
		cmd->outfile_path = ft_strdup(tokens[*i]);
		cmd->append_out = 1;
	}
	else if (!ft_strncmp(redir, "<<", 3))
	{
		cmd->infile = handle_heredoc(tokens[*i]);
		if (cmd->infile < 0)
			return (1);
	}
	(*i)++;
	return (0);
}

t_list *parse_tokens(char **tokens, t_req *req)
{
    int i;
	t_list *cmds;
	t_shell *current;

    i = 0;
    cmds = NULL;
	(void)req;
	while (tokens[i])
	{
		current = init_cmd();
		if (!current)
			return (NULL);
		while (tokens[i] && ft_strncmp(tokens[i], "|", 2))
		{
			if (is_redirect(tokens[i]))
			{
				if (set_redirection(current, tokens, &i))
				{
					free_cmds(cmds);
					return (NULL);
				}
			}
			else
				current->full_cmd = ft_double_extension(current->full_cmd, tokens[i++]);
		}
		ft_lstadd_back(&cmds, ft_lstnew(current));
		if (tokens[i])
			i++;
	}
	return (cmds);
}
