/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:47:57 by oyuhi             #+#    #+#             */
/*   Updated: 2024/11/20 17:59:33 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*remove_copied(char *mega_buffer)
{
	char	*remained_buffer;
	char	*temp;
	size_t	len;
	size_t	i;

	remained_buffer = NULL;
	if (!mega_buffer)
		return (NULL);
	temp = mega_buffer;
	while (*temp && *temp != '\n')
		temp++;
	if (*temp == '\n')
	{
		temp++;
		len = ft_strlen(temp);
		remained_buffer = (char *)malloc(len + 1);
		if (!remained_buffer)
		{
			free(mega_buffer);
			return (NULL);
		}
		i = 0;
		while (temp[i])
		{
			remained_buffer[i] = temp[i];
			i++;
		}
		remained_buffer[i] = '\0';
	}
	free(mega_buffer);
	return (remained_buffer);
}

char	*dup_till_newline(char *mega_buffer)
{
	size_t	len;
	char	*next_line;
	size_t	i;

	if (!mega_buffer)
		return (NULL);
	len = 0;
	while (mega_buffer[len] && mega_buffer[len] != '\n')
		len++;
	if (mega_buffer[len] == '\n')
		len++;
	next_line = (char *)malloc(len + 1);
	if (!next_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		next_line[i] = mega_buffer[i];
		i++;
	}
	next_line[i] = '\0';
	return (next_line);
}

char	*read_till_newline(int fd, char *mega_buffer)
{
	char	*buffer;
	ssize_t	bytesRead;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_strchr(mega_buffer, '\n') == NULL)
	{
		bytesRead = read(fd, buffer, BUFFER_SIZE);
		if (bytesRead <= 0)
			break ;
		buffer[bytesRead] = '\0';
		mega_buffer = ft_strjoin(mega_buffer, buffer);
		if (!mega_buffer)
			break ;
	}
	free(buffer);
	if (bytesRead < 0 || mega_buffer)
		return (NULL);
	return (mega_buffer);
}

char	*get_next_line(int fd)
{
	static char	*mega_buffer;
	char		*next_line;
	char		dummy[1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	mega_buffer = read_till_newline(fd, mega_buffer);
	if (!mega_buffer)
		return (NULL);
	next_line = dup_till_newline(mega_buffer);
	if (!next_line)
		return (NULL);
	mega_buffer = remove_copied(mega_buffer);
	return (next_line);
}

// create a list
// copy the content from file by each buffer size while founding \n
// searching for a \n in the list
// finding the last node of the list
// append a new node to the list
// after finding a \n, copy the line from the list
// measure the length
// malloc a new line sized the length
// copy the sentenct
// delete copied charaters in the list and keep unused charaters

// char	*join_buffer(char *mega_buffer, char *buffer)
// {
// 	size_t	mega_len;
// 	size_t	buf_len;
// 	char	*joined_buffer;
// 	size_t	i;

// 	if (!buffer)
// 		return (NULL);
// 	mega_len = ft_strlen(mega_buffer);
// 	buf_len = ft_strlen(buffer);
// 	joined_buffer = (char *)malloc(mega_len + buf_len + 1);
// 	if (!joined_buffer)
// 		return (NULL);
// 	i = 0;
// 	while (mega_buffer && *mega_buffer)
// 	{
// 		joined_buffer[i++] = (*mega_buffer);
// 		mega_buffer++;
// 	}
// 	while (*buffer)
// 	{
// 		joined_buffer[i++] = (*buffer);
// 		buffer++;
// 	}
// 	joined_buffer[i] = '\0';
// 	free(mega_buffer);
// 	return (joined_buffer);
// }

// int	search_newline(char *mega_buffer)
// {
// 	if (!mega_buffer)
// 		return (0);
// 	while (*mega_buffer)
// 	{
// 		if (*mega_buffer == '\n')
// 			return (1);
// 		mega_buffer++;
// 	}
// 	return (0);
// }