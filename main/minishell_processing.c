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

#include "../minishell.h"

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

static t_token	**expand_tokens(t_token **tokens, t_req *res)
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
	return (tokens);
}

static int	needs_retokenization(char *str)
{
	int		i;
	int		in_quotes;
	char	quote_char;

	i = 0;
	in_quotes = 0;
	quote_char = 0;
	while (str[i])
	{
		if (!in_quotes && (str[i] == '\'' || str[i] == '"'))
		{
			in_quotes = 1;
			quote_char = str[i];
		}
		else if (in_quotes && str[i] == quote_char)
		{
			in_quotes = 0;
			quote_char = 0;
		}
		else if (!in_quotes && str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_token	**process_input(char *output, t_req *res)
{
	char		*trimmed_output;
	char		*expanded_input;
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
	if (needs_retokenization(trimmed_output))
	{
		expanded_input = expand_str(trimmed_output, res->envp, QUOTE_NONE, res);
		free(trimmed_output);
		tokens = tokenize_input(expanded_input);
		free(expanded_input);
	}
	else
	{
		tokens = tokenize_input(trimmed_output);
		free(trimmed_output);
		if (tokens)
			tokens = expand_tokens(tokens, res);
	}
	if (!tokens)
		return (NULL);
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
