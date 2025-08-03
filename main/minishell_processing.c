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

int	needs_retokenization(char *str)
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

char	**process_input(char *output, t_req *res)//trimm input
{
	char		*trimmed_output;

	trimmed_output = ft_strtrim(output, " \t"); // prompttaki  baştaki ve sondaki boşluklar ile tabları temizler
	if (!trimmed_output || !trimmed_output[0])
	{
		if (trimmed_output)
			free(trimmed_output);
		return (NULL);
	}
	add_history(output); // aşağı yukarı tuşlarıyla geçmiş
	return (tokenize_and_validate(trimmed_output, res)); //tokenizera gider
}

int	execute_pipeline(char **tokens, t_req *res)
{
	t_list	*cmds;

	cmds = parse_tokens(tokens, res);
	if (!cmds)
		return (0);
	res->cmds = cmds;
	execute_cmds(cmds, res);
	if (!check_valid_tokens(tokens))
	{
		free_cmds(cmds);
		res->cmds = NULL;
		return (0);
	}
	if (tokens && tokens[0]) // son çalışan bilgisi için güncelleme
		res->envp = mini_setenv("_", tokens[0], res->envp, 1);
	
	free_cmds(cmds);
	res->cmds = NULL;
	return (1);
}
