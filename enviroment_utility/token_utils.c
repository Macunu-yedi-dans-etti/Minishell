/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:00:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/03 15:34:09 by haloztur         ###   ########.fr       */
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
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	has_quotes_or_variables(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*get_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*name;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (str[*i] == '_')
	{
		(*i)++;
		return (ft_strdup("_"));
	}
	if (!ft_isalnum(str[*i]) && str[*i] != '_')
		return (NULL); // Geçersiz variable name
		
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (NULL);
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, str + start, len + 1);
	return (name);
}

char	*expand_variable(char *str, int *i, t_req *res)
{
	char	*var_name;
	char	*value;
	
	(*i)++; // $ karakterini geç
	
	// Eğer string sonu ise $ döndür
	if (!str[*i])
		return (ft_strdup("$"));
	
	// Geçersiz karakter kontrolü
	if (!ft_isalnum(str[*i]) && str[*i] != '_' && str[*i] != '?')
		return (ft_strdup("$"));
	
	var_name = get_var_name(str, i);
	if (!var_name)
		return (ft_strdup("$"));
	
	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		free(var_name);
		return (ft_itoa(res->exit_stat));
	}
	if (ft_strncmp(var_name, "_", 2) == 0)
	{
		free(var_name);
		return (ft_strdup("minishell"));
	}
	
	value = mini_getenv(var_name, res->envp, 1);
	free(var_name);
	return (value ? ft_strdup(value) : ft_strdup(""));
}

// Basit quote ve variable expansion
char	*process_quotes_and_expand(char *input, t_req *res)
{
	char	*result;
	int		i;
	int		len;
	
	if (!input || !*input)
		return (ft_strdup(""));
	
	len = ft_strlen(input);
	result = malloc(len * 10 + 1000); // Daha büyük buffer
	if (!result)
		return (NULL);
	result[0] = '\0';
	
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			// Tek tırnak - literal
			i++; // Açan tırnağı geç
			while (input[i] && input[i] != '\'')
			{
				int rlen = ft_strlen(result);
				result[rlen] = input[i];
				result[rlen + 1] = '\0';
				i++;
			}
			if (input[i] == '\'')
				i++; // Kapatan tırnağı geç
		}
		else if (input[i] == '"')
		{
			// Çift tırnak - variable expansion
			i++; // Açan tırnağı geç
			while (input[i] && input[i] != '"')
			{
				if (input[i] == '$')
				{
					char *expanded = expand_variable(input, &i, res);
					if (expanded)
					{
						ft_strlcat(result, expanded, len * 10 + 1000);
						free(expanded);
					}
				}
				else
				{
					int rlen = ft_strlen(result);
					result[rlen] = input[i];
					result[rlen + 1] = '\0';
					i++;
				}
			}
			if (input[i] == '"')
				i++; // Kapatan tırnağı geç
		}
		else if (input[i] == '$')
		{
			// Tırnak dışında variable
			char *expanded = expand_variable(input, &i, res);
			if (expanded)
			{
				ft_strlcat(result, expanded, len * 10 + 1000);
				free(expanded);
			}
		}
		else
		{
			// Normal karakter
			int rlen = ft_strlen(result);
			result[rlen] = input[i];
			result[rlen + 1] = '\0';
			i++;
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
		if (tokens[i][0] != '\0') // Boş olmayan token varsa
			return (1);
		i++;
	}
	return (0); // Hepsi boş
}
