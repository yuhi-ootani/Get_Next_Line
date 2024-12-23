/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:47:52 by oyuhi             #+#    #+#             */
/*   Updated: 2024/12/22 10:56:15 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// ssize_t NULL
# include <unistd.h>
// malloc NULL free
# include <stdlib.h>
// SIZE_MAX
# include <stdint.h>

// if Buffer size is not defined, the below Buffer size will be used.
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

void	split_by_newline(char **next_line, char *newline_pos, char **mega_buf);
void	read_till_newline(int fd, char **mega_buf);
char	*get_next_line(int fd);

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
void	ft_strncpy(char *dest, const char *str, size_t len);
char	*ft_strjoin(char *mega_buf, char *buf);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif