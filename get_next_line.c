/*
Write a function named get_next_line which prototype should be:

char *get_next_line(int fd);

Your function must return a line that has been read from the file descriptor passed as parameter.
What we call a "line that has been read" is a succession of 0 to n characters that end with '\n' 
(ascii code 0x0a) or with End Of File (EOF). The line should be returned including the '\n' in 
case there is one at the end of the line that has been read. When you've reached the EOF, you 
must store the current buffer in a char * and return it. If the buffer is empty you must return 
NULL. In case of error return NULL. In case of not returning NULL, the pointer should be free-able.

Your program will be compiled with the flag -D BUFFER_SIZE=xx, which has to be used as the buffer 
size for the read calls in your functions. Your function must be memory leak free. When you've 
reached the EOF, your function should keep 0 memory allocated with malloc, except the line that has 
been returned. Calling your function get_next_line() in a loop will therefore allow you to read the 
text available on a file descriptor one line at a time until the end of the text, no matter the size 
of either the text or one of its lines. Make sure that your function behaves well when it reads from 
a file, from the standard output, from a redirection, etc... No call to another function will be done 
on the file descriptor between 2 calls of get_next_line(). Finally we consider that get_next_line() 
has an undefined behaviour when reading from a binary file.
*/

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char	*s1)
{
	int		i;
	char	*dup_s1;

	i = 0;
	dup_s1 = (char *)malloc((ft_strlen(s1) + 1 ) * sizeof(char));
	if (!dup_s1)
		return (free(dup_s1), NULL);
	while(s1[i] != '\0')
	{
		dup_s1[i] = s1[i];
		i++; 
	}
	dup_s1[i] = '\0';
	return (dup_s1);
}

char	*get_next_line(int fd)
{
	int			i;
	static int	j;
	static int	byte;
	static char	buffer[BUFFER_SIZE];
	char		line[70000];

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (1)
	{
		if (j >= byte)
		{
			byte = read(fd, buffer, BUFFER_SIZE);
			j = 0;
			if (byte <= 0)
				break ;
		}
		line[i++] = buffer[j++];
		if (buffer[j] == '\n')
			break;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

// #include <fcntl.h>
// int main(void)
// {
//     int fd = open("MrPotter.txt", O_RDONLY);
//     if (fd == -1)
//         return (-1);
// 	char *output;
//     while ((output = get_next_line(fd)) != NULL)
//     {
//     	printf("\033[0;31mLine:\033[0m %s\n", output);
//         free(output);
//     }
// 	close(fd);
//     return (0);
// }
