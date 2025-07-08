/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:08:03 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/08 12:08:03 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current_unit;
	int		counter;

	if (!lst)
		return (0);
	counter = 0;
	current_unit = lst;
	while (current_unit)
	{
		current_unit = current_unit->next;
		counter++;
	}
	return (counter);
}
