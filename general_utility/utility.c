/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:45:08 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/09 00:15:39 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    safe_close(int *fd)
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

char	**ft_double_extension(char **matrix, char *new_str) // envp = ft_double_extension(envp, new_entry);
{
	int		i;
	int		size;
	char	**new_matrix;

	i = 0;
	while (matrix && matrix[i]) // matrix saysını tutar mesela : "SHELL=/bin/bash", = matrix[0] &&  "PWD=/home/user",     = matrix[1] ve matrix[2] ise NULL olur gibi
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
		new_matrix[i++] = ft_strdup(new_str); // new_entry burada aslında matrixin sonuna eklenecek veriyi temsil ediyor
	new_matrix[i] = NULL;
	if (matrix)
		ft_free(matrix);
	return (new_matrix);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*temp;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	strip_newline(char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
		s[--len] = '\0';
}
