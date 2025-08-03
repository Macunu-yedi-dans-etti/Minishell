/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:00:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/03 17:35:50 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

// Basit variable expansion
static char	*expand_token_var(char *str, int *i, t_req *res)
{
	int		start = ++(*i); // $ karakterini geç
	char	*name, *value;
	
	if (!str[*i])
		return (ft_strdup("$"));
	if (str[*i] == '?')
		return ((*i)++, ft_itoa(res->exit_stat));
	if (str[*i] == '_')
		return ((*i)++, ft_strdup("minishell"));
	if (!ft_isalnum(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	
	if (start == *i)
		return (ft_strdup("$"));
	
	name = ft_substr(str, start, *i - start);
	value = mini_getenv(name, res->envp, 1);
	free(name);
	return (value ? value : ft_strdup(""));  // mini_getenv zaten ft_strdup döndürüyor!
}

// Quote validation fonksiyonu
int	validate_quotes(char *str)
{
	int		i;
	int		single_count;
	int		double_count;
	int		in_single;
	int		in_double;

	i = 0;
	single_count = 0;
	double_count = 0;
	in_single = 0;
	in_double = 0;
	
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			single_count++;
			in_single = !in_single;
		}
		else if (str[i] == '"' && !in_single)
		{
			double_count++;
			in_double = !in_double;
		}
		i++;
	}
	
	// Çift sayıda olmalı (açılan her tırnak kapatılmalı)
	return (single_count % 2 == 0 && double_count % 2 == 0);
}

// Ana işleme fonksiyonu - çok daha basit
char	*process_quotes_and_expand(char *input, t_req *res)
{
	char	*result = ft_strdup("");
	char	*temp, *expanded;
	int		i = 0;
	
	if (!input)
		return (result);
	
	// Quote validation
	if (!validate_quotes(input))
	{
		free(result);
		return (NULL); // Quote error
	}
	
	while (input[i])
	{
		if (input[i] == '\'') // Tek tırnak - literal
		{
			int start = ++i;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i])
			{
				temp = ft_substr(input, start, i - start);
				expanded = ft_strjoin(result, temp);
				free(result);
				free(temp);
				result = expanded;
				i++;
			}
		}
		else if (input[i] == '"') // Çift tırnak - variable expansion
		{
			i++;
			while (input[i] && input[i] != '"')
			{
				if (input[i] == '$')
				{
					temp = expand_token_var(input, &i, res);
					expanded = ft_strjoin(result, temp);
					free(result);
					free(temp);
					result = expanded;
				}
				else
				{
					char c[2] = {input[i++], '\0'};
					temp = ft_strjoin(result, c);
					free(result);
					result = temp;
				}
			}
			if (input[i] == '"')
				i++;
		}
		else if (input[i] == '$') // Tırnak dışı variable
		{
			temp = expand_token_var(input, &i, res);
			expanded = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = expanded;
		}
		else // Normal karakter
		{
			char c[2] = {input[i++], '\0'};
			temp = ft_strjoin(result, c);
			free(result);
			result = temp;
		}
	}
	
	return (result);
}

int	check_valid_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
			return (1);
		i++;
	}
	return (0);
}
