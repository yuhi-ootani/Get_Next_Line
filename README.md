# Get Next Line

## Summary  
This repository provides an implementation of the `get_next_line` function for reading from a file descriptor one line at a time, including the trailing newline (`\n`) when present. It conforms to the 42 School project specification: only `read`, `malloc`, and `free` are used, and it supports multiple file descriptors in parallel. :contentReference[oaicite:0]{index=0}

## Repository Structure  
- **`get_next_line.h`**: Declares `get_next_line(int fd)` and defines the `BUFFER_SIZE` macro, which can be overridden at compile time. :contentReference[oaicite:1]{index=1}  
- **`get_next_line.c`**: Contains the core logic that reads from `fd` into a buffer of size `BUFFER_SIZE`, concatenates until a newline is found or EOF, and returns a `malloc`-allocated string containing the next line (including `\n` if present). :contentReference[oaicite:2]{index=2}  
- **`get_next_line_utils.c`**: Provides helper functions for string operations: joining buffers, locating the newline, extracting the current line, and preserving leftovers for subsequent calls. :contentReference[oaicite:3]{index=3}  

All source files are written in standard C (100% of the codebase). :contentReference[oaicite:4]{index=4}

## Languages and Tools  
- **C (100.0%)**: Core language used for all implementations of `get_next_line`. :contentReference[oaicite:5]{index=5}  

## How to Use This Repository  
1. **Clone the repository**:  
   ```bash
   git clone https://github.com/yuhi-ootani/Get_Next_Line.git
   cd Get_Next_Line
   ``` :contentReference[oaicite:6]{index=6}

2. **Compile source files**:  
   There is no provided `Makefile`. Compile manually, for example:  
   ```bash
   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line.c get_next_line_utils.c
   ``` :contentReference[oaicite:7]{index=7}

3. **Link into your project**:  
   If you have a `main.c` that uses `get_next_line`, compile as:  
   ```bash
   gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o test_gnl
   ``` :contentReference[oaicite:8]{index=8}

4. **Usage Example (`main.c`)**:  
   ```c
   #include <fcntl.h>
   #include <stdio.h>
   #include "get_next_line.h"

   int main(void) {
       int   fd;
       char  *line;

       fd = open("example.txt", O_RDONLY);
       if (fd < 0)
           return (1);

       while ((line = get_next_line(fd)) != NULL) {
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


