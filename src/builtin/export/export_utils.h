/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 08:43:40 by musoysal          #+#    #+#             */
/*   Updated: 2025/08/17 17:41:02 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_UTILS_H
# define EXPORT_UTILS_H

# include "../../../minishell.h"

int		is_valid_identifier(char *str);
void	add_to_export_list(char ***export_list, char *var, char **envp);
void	remove_from_export_list(char ***export_list, char *var);

size_t	ft_strarrlen(char **arr);
void	ft_free_array(char **arr);
void	print_sorted_export(char **envp, char **export_list);

#endif 