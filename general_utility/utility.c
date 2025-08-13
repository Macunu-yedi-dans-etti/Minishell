/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:45:08 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/13 15:46:01 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	safe_close(int *fd)
{
	if (!fd)
		return ;
	if (*fd >= 0 && *fd != STDIN_FILENO && *fd != STDOUT_FILENO
		&& *fd != STDERR_FILENO)
	{
		close(*fd);
		*fd = -1;
	}
}

int	ft_find_chr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	free_matrix(char **matrix)
{
	int	j;

	if (!matrix)
		return ;
	j = 0;
	while (matrix[j])
		free(matrix[j++]);
	free(matrix);
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
	free_matrix(matrix);
	return (new_matrix);
}
