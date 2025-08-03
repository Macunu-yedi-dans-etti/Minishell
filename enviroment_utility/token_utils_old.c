/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:00:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/03 15:03:20 by haloztur         ###   ########.fr       */
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

char	*process_quotes_and_expand(char *str, t_req *res)
{
	char	*result;
	char	*temp;
	int		i, j;
	int		in_single, in_double;
	
	if (!str)
		return (NULL);
	
	result = malloc(ft_strlen(str) * 2 + 1);
	if (!result)
		return (NULL);
	
	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
		}
		else if (str[i] == '"' && !in_single)
		{
			in_double = !in_double;
			i++;
		}
		else if (str[i] == '$' && !in_single)
		{
			temp = expand_variable(str, &i, res);
			if (temp)
			{
				strcpy(result + j, temp);
				j += ft_strlen(temp);
				free(temp);
			}
		}
		else
			result[j++] = str[i++];
	}
	
	result[j] = '\0';
	
	// Quote eşleşme kontrolü
	if (in_single || in_double)
	{
		free(result);
		return (NULL);
	}
	
	return (result);
}

char	*expand_variable(char *str, int *i, t_req *res)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*result;

	(*i)++; // $ atla
	start = *i;
	
	// Özel değişkenler
	if (str[*i] == '?')
	{
		(*i)++;
		result = ft_itoa(res->exit_stat);
		return (result ? result : ft_strdup(""));
	}
	if (str[*i] == '_')
	{
		(*i)++;
		var_value = mini_getenv("_", res->envp, 0);
		return (var_value ? ft_strdup(var_value) : ft_strdup(""));
	}
	
	// Normal değişken
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	
	if (start == *i)
		return (ft_strdup("$"));
	
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	
	var_value = mini_getenv(var_name, res->envp, 0);
	free(var_name);
	
	return (var_value ? ft_strdup(var_value) : ft_strdup(""));
}

int	get_quote_type_and_validate(char *str)
{
	int	len = ft_strlen(str);
	
	if (len < 2)
		return (0); // Tırnak yok
	
	// Başlangıç ve bitiş tırnağını kontrol et
	if (str[0] == '\'' && str[len - 1] == '\'')
	{
		// Tek tırnak kontrolü - ortada başka tek tırnak olmamalı
		for (int i = 1; i < len - 1; i++)
		{
			if (str[i] == '\'')
				return (-1); // Quote error
		}
		return (1); // Tek tırnak
	}
	else if (str[0] == '"' && str[len - 1] == '"')
	{
		// Çift tırnak kontrolü - escape edilmemiş çift tırnak olmamalı
		for (int i = 1; i < len - 1; i++)
		{
			if (str[i] == '"' && (i == 1 || str[i-1] != '\\'))
				return (-1); // Quote error
		}
		return (2); // Çift tırnak
	}
	else if (str[0] == '\'' || str[0] == '"' || str[len - 1] == '\'' || str[len - 1] == '"')
	{
		return (-1); // Eşleşmeyen tırnak - quote error
	}
	
	return (0); // Tırnak yok
}

char	*process_single_quotes(char *str)
{
	int	len = ft_strlen(str);
	char *result;
	
	// Tek tırnak içindeki her şey literal
	result = malloc(len - 1); // Tırnakları çıkar
	if (!result)
		return (NULL);
	
	ft_strlcpy(result, str + 1, len - 1); // İlk ve son tırnağı atla
	return (result);
}

char	*process_double_quotes(char *str, t_req *res)
{
	int		len = ft_strlen(str);
	char	*content;
	char	*result;
	
	// Çift tırnak içeriğini al
	content = malloc(len - 1);
	if (!content)
		return (NULL);
	ft_strlcpy(content, str + 1, len - 1); // İlk ve son tırnağı atla
	
	// Variable expansion yap
	result = expand_variables_in_string(content, res);
	free(content);
	
	return (result);
}

char	*expand_no_quotes(char *str, t_req *res)
{
	// Tırnak yok, sadece variable expansion
	return (expand_variables_in_string(str, res));
}

char	*expand_variables_in_string(char *str, t_req *res)
{
	char	*result;
	char	*temp;
	int		i;
	
	result = malloc(ft_strlen(str) * 2 + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			temp = expand_variable(str, &i, res->envp);
			if (temp)
			{
				ft_strlcat(result, temp, ft_strlen(str) * 2 + 1);
				free(temp);
			}
		}
		else
		{
			int len = ft_strlen(result);
			result[len] = str[i];
			result[len + 1] = '\0';
			i++;
		}
	}
	
	return (result);
}

int	validate_quotes(char *str)
{
	int	i;
	int	single_count;
	int	double_count;
	int	in_single;
	int	in_double;

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
