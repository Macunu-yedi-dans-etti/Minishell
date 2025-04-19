/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:23:04 by haloztur          #+#    #+#             */
/*   Updated: 2024/11/13 15:23:04 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit(long n)
{
	int		count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	while (n / 10 != 0)
	{
		count++;
		n = n / 10;
	}
	count++;
	return (count);
}

static void	ft_putnbr(char *str, size_t number, int *index)
{
	if (number > 9)
	{
		ft_putnbr(str, number / 10, index);
		ft_putnbr(str, number % 10, index);
	}
	else
	{
		str[*index] = number + '0';
		(*index)++;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		index;
	long	number;

	number = n;
	str = (char *)malloc(sizeof(char) * (ft_digit(number) + 1));
	if (!str)
		return (NULL);
	index = 0;
	if (n < 0)
	{
		str[0] = '-';
		number = number * -1;
		index++;
	}
	ft_putnbr(str, (size_t)number, &index);
	str[index] = '\0';
	return (str);
}
