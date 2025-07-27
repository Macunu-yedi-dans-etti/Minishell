/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:19:52 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 21:19:52 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	determine_quote_type(int has_single, int has_double, int has_unquoted)
{
	if (has_single && !has_double && !has_unquoted)
		return (QUOTE_SINGLE);
	else if (has_double && !has_single && !has_unquoted)
		return (QUOTE_DOUBLE);
	else
		return (QUOTE_NONE);
}
