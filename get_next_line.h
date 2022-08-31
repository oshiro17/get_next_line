#include <libc.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
# endif
# ifndef OPEN_MAX
# define OPEN_MAX 256
# endif

size_t	ft_strlen(const char *s, char escape);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*ft_get_line(char *save);
char	*ft_save(char *save);
char    *get_next_line(int fd);
