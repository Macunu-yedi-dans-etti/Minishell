/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:58:13 by haloztur          #+#    #+#             */
/*   Updated: 2024/12/20 18:25:30 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FDS
#  define MAX_FDS 4242
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*next_line(int fd, char *s);
char	*new_line(char *s, char c);
char	*parse(char *s, char c);
int     gnl_strlen(char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
#endif
