/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaniyuhi <otaniyuhi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:47:55 by oyuhi             #+#    #+#             */
/*   Updated: 2024/11/23 15:55:27 by otaniyuhi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

void	ft_strncpy(char *dest, const char *str, size_t len)
{
	size_t	i;

	if (!dest || !str)
		return ;
	i = 0;
	while (i < len && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	while (i < len)
	{
		dest[i] = '\0';
		i++;
	}
}

char	*ft_strjoin(char *mega_buf, char *buf)
{
	size_t	len_mega;
	size_t	len_buf;
	char	*joined_buffer;

	if (!buf)
		return (NULL);
	len_buf = ft_strlen(buf);
	len_mega = 0;
	if (mega_buf)
		len_mega = ft_strlen(mega_buf);
	joined_buffer = (char *)malloc(len_mega + len_buf + 1);
	if (!joined_buffer)
	{
		free(mega_buf);
		return (NULL);
	}
	if (mega_buf)
	{
		ft_strncpy(joined_buffer, mega_buf, len_mega);
		free(mega_buf);
	}
	if (buf)
		ft_strncpy(joined_buffer + len_mega, buf, len_buf);
	joined_buffer[len_mega + len_buf] = '\0';
	return (joined_buffer);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (s_len - start < len)
		len = s_len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	ft_strncpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
