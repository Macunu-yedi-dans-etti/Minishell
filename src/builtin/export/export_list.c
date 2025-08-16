/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:00:49 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/16 15:31:48 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_utils.h"

static int	str_in_array(char **arr, char *str)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (ft_strncmp(arr[i], str, ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	add_to_export_list(char ***export_list, char *var, char **envp)
{
	int		len;
	int		i;
	char	**new_list;

	if (str_in_array(*export_list, var))
		return ;
	if (str_in_array(envp, var))
		return ;
	
	len = ft_strarrlen(*export_list);
	new_list = malloc(sizeof(char *) * (len + 2));
	if (!new_list)
		return ;
	i = 0;
	while (i < len)
	{
		new_list[i] = (*export_list)[i];
		i++;
	}
	new_list[len] = ft_strdup(var);
	new_list[len + 1] = NULL;
	free(*export_list);
	*export_list = new_list;
}

void	remove_from_export_list(char ***export_list, char *var)
{
	int		i;
	int		j;
	int		len;
	char	**new_list;

	len = ft_strarrlen(*export_list);
	new_list = malloc(sizeof(char *) * (len + 1));
	if (!new_list)
		return ;
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strncmp((*export_list)[i], var, ft_strlen(var)) != 0)
			new_list[j++] = (*export_list)[i];
		else
			free((*export_list)[i]);
		i++;
	}
	new_list[j] = NULL;
	free(*export_list);
	*export_list = new_list;
}
