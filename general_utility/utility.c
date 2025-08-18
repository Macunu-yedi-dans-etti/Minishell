/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:20:04 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/18 11:20:06 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_chr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_double_extension(char **matrix, char *new_str)
{
	int		i;
	int		size;
	char	**new_matrix;

	i = 0;
	while (matrix && matrix[i])
		i++;
	size = i + 1;
	if (new_str)
		size++;
	new_matrix = (char **)malloc(sizeof(char *) * size);
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix && matrix[i])
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	if (new_str)
		new_matrix[i++] = ft_strdup(new_str);
	new_matrix[i] = NULL;
	ft_double_free(&matrix);
	return (new_matrix);
}
