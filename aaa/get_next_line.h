#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096 // Set to 4KB
# endif

// Function Prototypes
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *mega_buf, char *buf);
char	*ft_strchr(char *s, char c);
char	*ft_strdup(char *s);
void	ft_strcpy(char *dest, const char *str);
char	*read_till_newline(int fd, char *mega_buffer);
char	*dup_till_newline(char *mega_buffer);
char	*remove_copied(char *mega_buffer);
char	*get_next_line(int fd);

#endif
