/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:47:57 by oyuhi             #+#    #+#             */
/*   Updated: 2024/11/19 19:08:01 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	remove_copied_content(t_list **list)
{
	t_list	*tmp;
	char	*remained_buffer;
	size_t	i_con;
	size_t	i_rem;

	if (!(*list))
		return ;
	while ((*list)->next)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free((*list));
		(*list) = tmp;
	}
	remained_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!remained_buffer)
		return ;
	i_con = 0;
	i_rem = 0;
	while ((*list)->content[i_con] != '\0' && (*list)->content[i_con] != '\n')
		i_con++;
	while ((*list)->content[i_con])
		remained_buffer[i_rem++] = (*list)->content[i_con++];
	remained_buffer[i_rem] = '\0';
	(*list)->content = remained_buffer;
}

void	copy_line(t_list *list, char *next_line)
{
	size_t	i_list;
	size_t	i_line;

	if (!list || !next_line)
		return ;
	i_line = 0;
	while (list)
	{
		i_list = 0;
		while (list->content[i_list])
		{
			if (list->content[i_list] == '\n')
			{
				next_line[i_line++] = '\n';
				next_line[i_line] = '\0';
				return ;
			}
			next_line[i_line++] = list->content[i_list++];
		}
		list = list->next;
	}
	next_line[i_line] = '\0';
}

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

char	*convert_to_line(t_list *list)
{
	size_t	length;
	char	*next_line;

	if (!list)
		return (NULL);
	length = count_length(list);
	next_line = (char *)malloc(length + 1);
	if (!next_line)
		return (NULL);
	copy_line(list, next_line);
	return (next_line);
}

t_list	*find_last_node(t_list **list)
{
	t_list	*current_node;

	if (!list)
		return (NULL);
	current_node = (*list);
	while (current_node->next)
		current_node = current_node->next;
	return (current_node);
}

char	*add_buffer_to_list(char *mega_buffer, char *buffer)
{
	size_t	mega_len;
	size_t	buf_len;
	char	*joined_buffer;
	size_t	i;

	if (!mega_buffer || !buffer)
		return ;
	mega_len = ft_strlen(mega_buffer);
	buf_len = ft_strlen(buffer);
	joined_buffer = (char *)malloc(mega_len + buf_len + 1);
	if (!joined_buffer)
		return (NULL);
	while (*mega_buffer)
	{
		joined_buffer[i++] == (*mega_buffer);
		mega_buffer++;
	}
	while (*buffer)
	{
		joined_buffer[i++] == (*buffer);
		buffer++;
	}
	joined_buffer[i] == '\0';
	return (joined_buffer);
}

int	search_newline_in_buf(char *mega_buffer)
{
	if (!mega_buffer)
		return (0);
	while (*mega_buffer)
	{
		if (*mega_buffer == '\n')
			return (1);
		mega_buffer++;
	}
	return (0);
}

void	create_list_till_newline(int fd, char *mega_buffer)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytesRead;

	while (!search_newline_in_buf(mega_buffer) && (bytesRead = read(fd, buffer,
				BUFFER_SIZE)) > 0)
	{
		buffer[bytesRead] = '\0';
		mega_buffer = add_buffer_to_list(mega_buffer, buffer);
		if (!mega_buffer)
			return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static char	*mega_buffer;
	char		*next_line;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) < 0)
		return (NULL);
	create_list_till_newline(fd, mega_buffer);
	if (!mega_buffer)
		return (NULL);
	next_line = convert_to_line(mega_buffer);
	remove_copied_content(mega_buffer);
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