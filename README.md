Summary
This repository provides an implementation of the get_next_line function for reading from a file descriptor one line at a time, including the trailing newline (\n) when present. 
github.com
github.com
 It conforms to the 42 School project specification: only read, malloc, and free are used, and it supports multiple file descriptors in parallel. 
github.com
github.com

Repository Contents
get_next_line.h

Declares get_next_line(int fd) and defines BUFFER_SIZE, which can be overridden at compile time. 
github.com
github.com

get_next_line.c

Core logic that reads from fd into a buffer of size BUFFER_SIZE, concatenates until a newline is found or EOF, and returns a malloc-allocated string containing the next line (including \n if present). 
github.com
github.com

get_next_line_utils.c

Helper functions for string operations: joining buffers, locating the newline, extracting the current line, and preserving leftovers for subsequent calls. 
github.com
github.com

All source files are written in standard C (100% of the codebase). 
github.com
github.com

Installation / Compilation
Clone the repository

bash
Copy
Edit
git clone https://github.com/yuhi-ootani/Get_Next_Line.git
cd Get_Next_Line
github.com
github.com

Compile source files
There is no provided Makefile. Compile manually, for example:

bash
Copy
Edit
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line.c get_next_line_utils.c
github.com
github.com

Link into your project
If you have a main.c that uses get_next_line, compile as:

bash
Copy
Edit
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o test_gnl
github.com
github.com

Usage Example
c
Copy
Edit
// main.c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int  fd;
    char *line;

    fd = open("example.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
Compile and run:

bash
Copy
Edit
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o demo
./demo
This prints each line of example.txt, including the newline character. 
github.com
github.com

Key Behavior and Constraints
Line-by-Line Reading

Each call to get_next_line(fd) returns exactly one line from fd, including the trailing \n if it exists; on EOF, it returns any remaining text without \n, then NULL. 
github.com
github.com

Multiple File Descriptors

The implementation maintains a separate static buffer per fd, allowing interleaved calls (e.g., get_next_line(fd1), then get_next_line(fd2), then get_next_line(fd1) resumes from the correct position). 
github.com
github.com

BUFFER_SIZE Macro

Defines how many bytes are read per read call; changing -D BUFFER_SIZE=<size> affects performance and memory usage. 
github.com
github.com

Memory Management

The caller must free each returned string. Internally, buffers are dynamically allocated and adjusted for each line. 
github.com
github.com

