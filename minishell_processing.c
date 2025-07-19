/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:19:38 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 19:19:38 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_tokens(t_token **tokens, t_req *res)
{
	char	*old;
	int		i;

	i = 0;
	while (tokens && tokens[i])
	{
		old = tokens[i]->str;
		tokens[i]->str = expand_str(old, res->envp, tokens[i]->quote, res);
		free(old);
		i++;
	}
	return (i);
}

static int	check_valid_tokens(t_token **tokens)
{
	int	has_valid_tokens;
	int	i;

	has_valid_tokens = 0;
	i = 0;
	while (tokens && tokens[i])
	{
		if (tokens[i]->str && (tokens[i]->str[0] != '\0'
				|| tokens[i]->quote != QUOTE_NONE))
		{
			has_valid_tokens = 1;
			break ;
		}
		i++;
	}
	return (has_valid_tokens);
}

t_token	**process_input(char *output, t_req *res)
{
	char		*trimmed_output;
	t_token		**tokens;

	trimmed_output = ft_strtrim(output, " \t");
	if (!trimmed_output || !trimmed_output[0])
	{
		if (trimmed_output)
			free(trimmed_output);
		return (NULL);
	}
	add_history(output);
	append_history_file(".minishell_history", output);
	tokens = tokenize_input(trimmed_output);
	free(trimmed_output);
	if (!tokens)
		return (NULL);
	expand_tokens(tokens, res);
	if (!check_valid_tokens(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}

int	execute_pipeline(t_token **tokens, t_req *res)
{
	t_list	*cmds;

	cmds = parse_tokens(tokens, res);
	if (!cmds)
		return (0);
	execute_cmds(cmds, res);
	free_cmds(cmds);
	return (1);
}
