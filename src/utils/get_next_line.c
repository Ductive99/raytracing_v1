/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 21:47:18 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len1)
		result[i] = s1[i];
	i = -1;
	while (++i < len2)
		result[len1 + i] = s2[i];
	result[len1 + len2] = '\0';
	free(s1);
	return (result);
}

static char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*extract_line(char **storage)
{
	char	*line;
	char	*newline_pos;
	char	*temp;
	size_t	len;

	if (!*storage || !**storage)
		return (NULL);
	newline_pos = ft_strchr_gnl(*storage, '\n');
	if (newline_pos)
	{
		len = newline_pos - *storage + 1;
		line = malloc(len + 1);
		if (!line)
			return (NULL);
		ft_memcpy(line, *storage, len);
		line[len] = '\0';
		temp = malloc(ft_strlen(newline_pos + 1) + 1);
		if (!temp)
			return (free(line), NULL);
		ft_memcpy(temp, newline_pos + 1, ft_strlen(newline_pos + 1) + 1);
		free(*storage);
		*storage = temp;
		return (line);
	}
	return (line = *storage, *storage = NULL, line);
}

/**
 * get_next_line - Read a line from a file descriptor
 *
 * @fd: File descriptor to read from
 *
 * Return: Line read including newline, or NULL if end or error
 */
char	*get_next_line(int fd)
{
	static char	*storage;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (storage)
			return (free(storage), storage = NULL, NULL);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr_gnl(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(storage), storage = NULL, (NULL));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		storage = ft_strjoin_gnl(storage, buffer);
		if (!storage)
			return (NULL);
	}
	return (extract_line(&storage));
}
