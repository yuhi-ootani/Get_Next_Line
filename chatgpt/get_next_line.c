#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *remainder;
    char *buffer;
    char *newline_pos;
    char *temp;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    
    // Allocate buffer on the heap
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);

    // Read until a newline is found
    while ((newline_pos = ft_strchr(remainder, '\n')) == NULL)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            return (NULL);
        }
        if (bytes_read == 0)
            break;
        buffer[bytes_read] = '\0';
        remainder = ft_strjoin(remainder, buffer);
        if (!remainder)
        {
            free(buffer);
            return (NULL);
        }
    }
    free(buffer);

    // If newline is found, extract the line
    if (newline_pos)
    {
        size_t line_length = newline_pos - remainder + 1;
        char *line = ft_substr(remainder, 0, line_length);
        temp = ft_substr(remainder, line_length, ft_strlen(remainder) - line_length);
        free(remainder);
        remainder = temp;
        return (line);
    }

    // If no newline, return the remainder if any
    if (remainder && *remainder)
    {
        char *line = ft_substr(remainder, 0, ft_strlen(remainder));
        free(remainder);
        remainder = NULL;
        return (line);
    }

    free(remainder);
    remainder = NULL;
    return (NULL);
}
