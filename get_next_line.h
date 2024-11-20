/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:47:52 by oyuhi             #+#    #+#             */
/*   Updated: 2024/11/20 16:11:36 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// ssize_t NULL
# include <unistd.h>
// malloc NULL
# include <stdlib.h>

// if Buffer size is not defined, the below Buffer size will be used.
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*remove_copied(char *mega_buffer);
char	*dup_till_newline(char *mega_buffer);
char	*join_buffer(char *mega_buffer, char *buffer);
int		search_newline(char *mega_buffer);
char	*read_till_newline(int fd, char *mega_buffer);
char	*get_next_line(int fd);

size_t	ft_strlen(char *str);
char	*ft_strdup(char *s);
char	*ft_strchr(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strcpy(char *dest, char *str);

#endif