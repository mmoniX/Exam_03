#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

int		ft_strlen(char *str);
char	*ft_strdup(char	*s1);
char	*get_next_line(int fd);

#endif