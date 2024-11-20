#include "get_next_line.h"

// Calculate the length of a string
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

// Duplicate a string
char	*ft_strdup(char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// Copy a string from src to dest
void	ft_strcpy(char *dest, const char *str)
{
	while (*str)
		*dest++ = *str++;
	*dest = '\0';
}

// Join two strings and free the first string
char	*ft_strjoin(char *mega_buf, char *buf)
{
	size_t	len_mega;
	size_t	len_buf;
	char	*joined_buffer;

	len_mega = mega_buf ? ft_strlen(mega_buf) : 0;
	len_buf = buf ? ft_strlen(buf) : 0;
	if (!mega_buf && !buf)
		return (NULL);
	joined_buffer = (char *)malloc(len_mega + len_buf + 1);
	if (!joined_buffer)
		return (NULL);
	if (mega_buf)
		ft_strcpy(joined_buffer, mega_buf);
	else
		joined_buffer[0] = '\0';
	if (buf)
		ft_strcpy(joined_buffer + len_mega, buf);
	joined_buffer[len_mega + len_buf] = '\0';
	if (mega_buf)
		free(mega_buf); // Free the original buffer to prevent memory leaks
	return (joined_buffer);
}

// Find the first occurrence of character c in string s
char	*ft_strchr(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

// Read from fd until a newline character is found
char	*read_till_newline(int fd, char *mega_buffer)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytesRead;

	while (ft_strchr(mega_buffer, '\n') == NULL && (bytesRead = read(fd, buffer,
				BUFFER_SIZE)) > 0)
	{
		buffer[bytesRead] = '\0';
		mega_buffer = ft_strjoin(mega_buffer, buffer);
		if (!mega_buffer)
			return (NULL);
	}
	if (bytesRead == -1)
	{
		// Read error
		free(mega_buffer);
		return (NULL);
	}
	return (mega_buffer);
}

// Duplicate characters from mega_buffer up to and including the newline
char	*dup_till_newline(char *mega_buffer)
{
	size_t	len;
	char	*next_line;
	size_t	i;

	len = 0;
	if (!mega_buffer)
		return (NULL);
	while (mega_buffer[len] && mega_buffer[len] != '\n')
		len++;
	if (mega_buffer[len] == '\n')
		len++; // Include the newline character
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

// Remove the duplicated part from mega_buffer and keep the remaining
char	*remove_copied(char *mega_buffer)
{
	char	*remained_buffer;
	char	*temp;
	size_t	len;
	size_t	i;

	remained_buffer = NULL;
	temp = mega_buffer;
	if (!mega_buffer)
		return (NULL);
	while (*temp && *temp != '\n')
		temp++;
	if (*temp == '\n')
		temp++; // Move past the newline character
	len = ft_strlen(temp);
	if (len > 0)
	{
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
	free(mega_buffer); // Free the original buffer correctly
	return (remained_buffer);
}

// Main get_next_line function
char	*get_next_line(int fd)
{
	static char	*mega_buffer = NULL;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	mega_buffer = read_till_newline(fd, mega_buffer);
	if (!mega_buffer)
		return (NULL);
	next_line = dup_till_newline(mega_buffer);
	if (!next_line)
	{
		free(mega_buffer);
		mega_buffer = NULL;
		return (NULL);
	}
	mega_buffer = remove_copied(mega_buffer);
	return (next_line);
}
