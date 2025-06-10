/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:21:51 by haloztur          #+#    #+#             */
/*   Updated: 2024/12/22 12:48:56 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*parse(char *s, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	str = (char *)malloc((gnl_strlen(s) - i) + 1);
	if (!str)
		return (NULL);
	i++;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

char	*new_line(char *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*next_line(int fd, char *s)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	i = 1;
	while (!ft_strchr(s, '\n') && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
		{
			free(str);
			return (NULL);
		}
		str[i] = '\0';
		s = gnl_strjoin(s, str);
	}
	free(str);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = next_line(fd, line);
	if (line)
	{
		str = new_line(line, '\n');
		line = parse(line, '\n');
		return (str);
	}
	return (NULL);
}
