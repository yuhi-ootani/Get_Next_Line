#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

// Include your get_next_line function and its dependencies here
// For example:
// char *get_next_line(int fd);

// Helper function to compare lines and indicate correctness
void compare_and_print_lines(char *gnl_line, char *original_line, int line_number, int *differences) {
    if (gnl_line == NULL && original_line == NULL) {
        // End of both inputs
        return;
    } else if (gnl_line == NULL || original_line == NULL) {
        printf("Difference detected at line %d:\n", line_number);
        printf("get_next_line returned: %s\n", gnl_line ? gnl_line : "NULL");
        printf("Original content: %s\n", original_line ? original_line : "NULL");
        (*differences)++;
    } else if (strcmp(gnl_line, original_line) != 0) {
        printf("Difference detected at line %d:\n", line_number);
        printf("get_next_line returned: %s", gnl_line);
        printf("Original content: %s", original_line);
        (*differences)++;
    } else {
        printf("Line %d is correct: %s", line_number, gnl_line);
    }
}

int main(int argc, char **argv) {
    int files_processed = 0;

    if (argc > 1) {
        // Process files provided as command-line arguments
        for (int i = 1; i < argc; i++) {
            char *filename = argv[i];
            printf("Processing file: %s\n", filename);
            int fd = open(filename, O_RDONLY);
            if (fd < 0) {
                perror("Error opening file with open");
                continue;
            }
            FILE *fp = fopen(filename, "r");
            if (!fp) {
                perror("Error opening file with fopen");
                close(fd);
                continue;
            }

            char *gnl_line;
            char *original_line = NULL;
            size_t len = 0;
            int line_number = 1;
            int differences = 0;

            while (1) {
                // Read a line using get_next_line
                gnl_line = get_next_line(fd);

                // Read a line using getline
                ssize_t read = getline(&original_line, &len, fp);
                if (read == -1) {
                    free(original_line);
                    original_line = NULL;
                }

                // Compare the lines
                if (gnl_line == NULL && original_line == NULL) {
                    // End of both inputs
                    break;
                }
                compare_and_print_lines(gnl_line, original_line, line_number, &differences);

                // Free the line read by get_next_line
                free(gnl_line);
                gnl_line = NULL;

                line_number++;
            }

            if (differences == 0) {
                printf("No differences detected in file %s.\n", filename);
            } else {
                printf("Total differences found in file %s: %d\n", filename, differences);
            }

            fclose(fp);
            close(fd);
            files_processed++;
        }
    } else {
        // No files provided, read from stdin
        printf("Reading from standard input (stdin). Type your input and press Ctrl+D when done:\n");
        int fd = STDIN_FILENO; // File descriptor for stdin
        char *gnl_line;

        while ((gnl_line = get_next_line(fd)) != NULL) {
            // Output the line read by get_next_line
            printf("get_next_line returned: %s", gnl_line);
            free(gnl_line);
        }
    }

    // If no files were processed and no input was read from stdin, process files in the "files" directory
    if (argc == 1 && files_processed == 0) {
        DIR *dir;
        struct dirent *entry;
        char *directory = "files";
        char filepath[1024];

        dir = opendir(directory);
        if (dir == NULL) {
            perror("Unable to open directory");
            return 1;
        }

        while ((entry = readdir(dir)) != NULL) {
            // Skip "." and ".."
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            // Only process .txt files
            if (strstr(entry->d_name, ".txt") != NULL) {
                snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);
                printf("\nProcessing file: %s\n", filepath);
                int fd = open(filepath, O_RDONLY);
                if (fd < 0) {
                    perror("Error opening file with open");
                    continue;
                }
                FILE *fp = fopen(filepath, "r");
                if (!fp) {
                    perror("Error opening file with fopen");
                    close(fd);
                    continue;
                }

                char *gnl_line;
                char *original_line = NULL;
                size_t len = 0;
                int line_number = 1;
                int differences = 0;

                while (1) {
                    // Read a line using get_next_line
                    gnl_line = get_next_line(fd);

                    // Read a line using getline
                    ssize_t read = getline(&original_line, &len, fp);
                    if (read == -1) {
                        free(original_line);
                        original_line = NULL;
                    }

                    // Compare the lines
                    if (gnl_line == NULL && original_line == NULL) {
                        // End of both inputs
                        break;
                    }
                    compare_and_print_lines(gnl_line, original_line, line_number, &differences);

                    // Free the line read by get_next_line
                    free(gnl_line);
                    gnl_line = NULL;

                    line_number++;
                }

                if (differences == 0) {
                    printf("No differences detected in file %s.\n", entry->d_name);
                } else {
                    printf("Total differences found in file %s: %d\n", entry->d_name, differences);
                }

                fclose(fp);
                close(fd);
                files_processed++;
            }
        }
        closedir(dir);
    }

    return 0;
}


// void	handle_allocation_error(char **next_line, char **mega_buf)
// {
// 	if (*next_line)
// 	{
// 		free(*next_line);
// 		*next_line = NULL;
// 	}
// 	if (*mega_buf)
// 	{
// 		free(*mega_buf);
// 		*mega_buf = NULL;
// 	}
// }

// int	err_free(char *checked_char, char **freed_char)
// {
// 	if (!checked_char)
// 	{
// 		if (*freed_char)
// 		{
// 			free(*freed_char);
// 			*freed_char = NULL;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

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

// char	*remove_copied(char *mega_buffer)
// {
// 	char	*remained_buffer;
// 	char	*temp;
// 	size_t	len;
// 	size_t	i;

// 	remained_buffer = NULL;
// 	if (!mega_buffer)
// 		return (NULL);
// 	temp = mega_buffer;
// 	while (*temp && *temp != '\n')
// 		temp++;
// 	if (*temp == '\n')
// 	{
// 		temp++;
// 		len = ft_strlen(temp);
// 		remained_buffer = (char *)malloc(len + 1);
// 		if (!remained_buffer)
// 		{
// 			free(mega_buffer);
// 			return (NULL);
// 		}
// 		i = 0;
// 		while (temp[i])
// 		{
// 			remained_buffer[i] = temp[i];
// 			i++;
// 		}
// 		remained_buffer[i] = '\0';
// 	}
// 	free(mega_buffer);
// 	return (remained_buffer);
// }

// char	*dup_till_newline(char *mega_buffer)
// {
// 	size_t	len;
// 	char	*next_line;
// 	size_t	i;

// 	if (!mega_buffer)
// 		return (NULL);
// 	len = 0;
// 	while (mega_buffer[len] && mega_buffer[len] != '\n')
// 		len++;
// 	if (mega_buffer[len] == '\n')
// 		len++;
// 	next_line = (char *)malloc(len + 1);
// 	if (!next_line)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		next_line[i] = mega_buffer[i];
// 		i++;
// 	}
// 	next_line[i] = '\0';
// 	return (next_line);
// }

// char	*ft_strdup(char *s)
// {
// 	size_t	len;
// 	int		i;
// 	char	*dup;

// 	len = ft_strlen(s);
// 	dup = (char *)malloc((len + 1) * sizeof(char));
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }