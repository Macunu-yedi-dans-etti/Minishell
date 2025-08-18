/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 08:22:56 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/18 11:25:19 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	num;
	void	*p;

	num = count * size;
	p = malloc(num);
	if (!p)
		return (NULL);
	ft_bzero(p, num);
	return (p);
}
