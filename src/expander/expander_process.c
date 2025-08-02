/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*process_variable(const char *input, int *i, char **envp,
			t_req *req)
{
	char	*expanded;

	expanded = expand_var(input, i, envp, req);
	if (!expanded)
		return (NULL);
	return (expanded);
}

static char	*process_character(char *result, const char *input, int *i,
			int *len)
{
	if (should_escape_char(input, *i, 2))
		(*i)++;
	result = append_char(result, input[(*i)++], len);
	return (result);
}

static char	*handle_dollar_sign(char *result, const char *input, int *i,
			t_process_data *data) // expand_str(trimmed_output, res->envp, QUOTE_NONE, res);
{
	char	*expanded;

	expanded = process_variable(input, i, data->envp, data->req);// expand_var(input, i, data->envp, data->req);
	if (!expanded)
		return (free(result), NULL);
	result = append_str(result, expanded, data->len); // result = ft_strjoin_free(result, expanded);
	free(expanded);
	return (result);
}

static void	setup_data(t_process_data *data, char **envp, t_req *req, int *len)
{
	data->envp = envp;
	data->req = req;
	data->len = len;
}

char	*process_input_loop(const char *input, char **envp, t_req *req)
{
	int				i;
	int				len;
	char			*result;
	t_process_data	data;

	i = 0;
	len = 1;
	setup_data(&data, envp, req, &len);
	result = initialize_result();
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$') // Eğer $ karakteri varsa, değişken genişletme işlemi yapar
		{
			result = handle_dollar_sign(result, input, &i, &data);
			if (!result)
				return (NULL);
			continue ;
		}
		result = process_character(result, input, &i, &len);
		if (!result)
			return (NULL);
	}
	return (result);
}

/*
Step-by-step processing:

i=0: 'H' → process_character → result="H" (len=2)
i=1: 'e' → process_character → result="He" (len=3)  
i=2: 'l' → process_character → result="Hel" (len=4)
i=3: 'l' → process_character → result="Hell" (len=5)
i=4: 'o' → process_character → result="Hello" (len=6)
i=5: ' ' → process_character → result="Hello " (len=7)

i=6: '$' → handle_dollar_sign:
    ↳ process_variable() → expand $USER → "haloztur"
    ↳ append_str() → result="Hello haloztur" (len=15)
    ↳ i=11 (skipped $USER)

i=11: ' ' → process_character → result="Hello haloztur " (len=16)
i=12: 'w' → process_character → result="Hello haloztur w" (len=17)
i=13: 'o' → process_character → result="Hello haloztur wo" (len=18)
i=14: 'r' → process_character → result="Hello haloztur wor" (len=19)
i=15: 'l' → process_character → result="Hello haloztur worl" (len=20)
i=16: 'd' → process_character → result="Hello haloztur world" (len=21)

Final: "Hello haloztur world"
*/