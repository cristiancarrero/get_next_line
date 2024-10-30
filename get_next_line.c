/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caguerre <caguerre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by caguerre          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by caguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free_storage(char **storage)
{
	free(*storage);
	*storage = NULL;
	return (NULL);
}

static char	*ft_read_buffer(int fd, char *storage, char *buffer)
{
	ssize_t	bytes;

	bytes = 1;
	while (!ft_strchr(storage, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_free_storage(&storage));
		buffer[bytes] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (NULL);
	}
	return (storage);
}

static char	*ft_process_read(int fd, char *storage)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_storage(&storage));
	storage = ft_read_buffer(fd, storage, buffer);
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ft_free_storage(&storage));
	if (!storage)
	{
		storage = malloc(1);
		if (!storage)
			return (NULL);
		storage[0] = '\0';
	}
	storage = ft_process_read(fd, storage);
	if (!storage)
		return (NULL);
	line = ft_get_line(storage);
	if (!line)
		return (ft_free_storage(&storage));
	storage = ft_process_storage(storage);
	return (line);
}
