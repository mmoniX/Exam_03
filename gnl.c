/*
Write a function named get_next_line which prototype should be:

char *get_next_line(int fd);

Your function must return a line that has been read from the file descriptor passed as parameter.
What we call a "line that has been read" is a succession of 0 to n characters that end with '\n' (ascii code 0x0a)
or with End Of File (EOF). The line should be returned including the '\n' in case there is one at the end of the 
line that has been read. When you've reached the EOF, you must store the current buffer in a char * and return it. 
If the buffer is empty you must return NULL. In case of error return NULL. In case of not returning NULL, the pointer 
should be free-able. Your program will be compiled with the flag -D BUFFER_SIZE=xx, which has to be used as the buffer 
size for the read calls in your functions. Your function must be memory leak free. When you've reached the EOF, your 
function should keep 0 memory allocated with malloc, except the line that has been returned. Calling your function 
get_next_line() in a loop will therefore allow you to read the text available on a file descriptor one line at a time 
until the end of the text, no matter the size of either the text or one of its lines. Make sure that your function 
behaves well when it reads from a file, from the standard output, from a redirection, etc... No call to another function
will be done on the file descriptor between 2 calls of get_next_line(). Finally we consider that get_next_line() has an 
undefined behaviour when reading from a binary file.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char *get_next_line(int fd)
{
    int     byte;
    char    buffer;
    char    *line;
    int     i;

    if (BUFFER_SIZE < 1 || fd < 0)
        return (NULL);
    i = 0;
    line = (char *)malloc(10000000);
    if (!line)
        return (free(line), NULL);
    byte = read(fd, &buffer, 1);
    while (byte > 0)
    {
        line[i] = buffer;
        i++;
        if(buffer == '\n' || buffer == EOF)
            break ;
        byte = read(fd, &buffer, 1);
    }
    if (i == 0 || byte < 0)
        return (free (line), NULL);
    line[i] = '\0';
    return (line);
}

int main(void)
{
    int fd = open("MrPotter.txt", O_RDONLY);
    if (fd == -1)
        return (-1);
	char *line = get_next_line(fd);
	printf("Line1: %s\n", line);
	free(line);
	close(fd);
    return (0);
}