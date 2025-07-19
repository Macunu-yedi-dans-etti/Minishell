/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 17:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_env_char(char c)
{
	return (ft_isalnum((unsigned char)c) || c == '_');
}

int	get_var_len(const char *s)
{
	int	i;

	i = 0;
	if (s[0] == '?')
		return (1);
	while (s[i] && is_env_char(s[i]))
		i++;
	return (i);
}

static void	copy_to_new_str(char *new_str, char *dst, const char *src, int len)
{
	int	src_len;

	src_len = ft_strlen(src);
	ft_memcpy(new_str, dst, len - 1);
	ft_memcpy(new_str + len - 1, src, src_len + 1);
}

char	*append_str(char *dst, const char *src, int *len)
{
	int		src_len;
	char	*new_str;

	src_len = ft_strlen(src);
	new_str = malloc(*len + src_len);
	if (!new_str)
		return (NULL);
	copy_to_new_str(new_str, dst, src, *len);
	free(dst);
	*len += src_len;
	return (new_str);
}

char	*append_char(char *dst, char c, int *len)
{
	char	*new_str;

	new_str = malloc(*len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, dst, *len - 1);
	new_str[*len - 1] = c;
	new_str[*len] = '\0';
	free(dst);
	(*len)++;
	return (new_str);
}
