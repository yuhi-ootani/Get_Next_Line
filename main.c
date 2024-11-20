#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Prototype of your get_next_line function
char	*get_next_line(int fd);

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_number;

	// Check for correct number of command-line arguments
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	// Open the file for reading
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (EXIT_FAILURE);
	}
	line_number = 1;
	// Read lines until get_next_line returns NULL
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d:\n%s", line_number, line);
		free(line); // Free the allocated memory for the line
		line_number++;
	}
	// Close the file
	if (close(fd) < 0)
	{
		perror("Error closing file");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
