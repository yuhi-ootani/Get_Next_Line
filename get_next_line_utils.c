/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:47:55 by oyuhi             #+#    #+#             */
/*   Updated: 2024/11/20 18:10:12 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
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

char	*ft_strdup(char *s)
{
	size_t	len;
	int		i;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	ft_strcpy(char *dest, char *str)
{
	while (*str)
		*dest++ = *str++;
	*dest = '\0';
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
		return (NULL);
	if (mega_buf)
		ft_strcpy(joined_buffer, mega_buf);
	if (buf)
		ft_strcpy(joined_buffer + len_mega, buf);
	joined_buffer[len_mega + len_buf] = '\0';
	return (joined_buffer);
}
