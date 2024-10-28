/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static void	ft_strcpy(char *dst, char *src, size_t *i)
{
	size_t	j;

	j = 0;
	while (src[j])
	{
		dst[*i] = src[j];
		(*i)++;
		j++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	if (!s1)
	{
		s1 = malloc(sizeof(char) + 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (free(s1), NULL);
	i = 0;
	ft_strcpy(str, s1, &i);
	ft_strcpy(str, s2, &i);
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_update_storage(char *storage)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
		return (free(storage), NULL);
	new = malloc(sizeof(char) * (ft_strlen(storage) - i + 1));
	if (!new)
		return (free(storage), NULL);
	i++;
	j = 0;
	while (storage[i])
		new[j++] = storage[i++];
	new[j] = '\0';
	free(storage);
	return (new);
}
