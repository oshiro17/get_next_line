#include "get_next_line.h"
#include <string.h>

size_t	ft_strlen(const char *s, char escape)
{
	size_t	i;

	i = 0;
	if (!s)
		return(i);
	while (s[i] != escape)
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1,'\0') + ft_strlen(s2,'\0') + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
	{
		while (s1[++i] != '\0')
			str[i] = s1[i];
	}
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[ft_strlen(s1,'\0') + ft_strlen(s2,'\0')] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s,'\0')]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_get_line(char *save)
{
	int		i;
	char	*to_line;

	if (!save[0])
		return (NULL);
	to_line = (char *)malloc(sizeof(char) * ((ft_strlen(save,'\n')) + 2));
	if (!to_line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		to_line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		to_line[i] = save[i];
		i++;
	}
	to_line[i] = '\0';
	return (to_line);
}
// char	*ft_get_line(char *save)
// {
// 	char	*to_line;
// 	int		i;

// 	i = 0;
// 	if (!to_line[0])
// 		return (NULL);
// 	to_line = (char *)malloc(ft_strlen(save, '\n') + 2);
// 	if (!to_line)
// 		return (NULL);
// 	while (save[i] && save[i] != '\n')
// 	{
// 		to_line[i] = save[i];
// 		i++;
// 	}
// 	if (save[i] == '\n')
// 	{
// 		to_line[i] = save[i];
// 		i++;
// 	}
// 	to_line[i] = '\0';
// 	return (to_line);
// }

char	*ft_save(char *save)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(save,'\0') - i + 1));
	if (!s)
		return (NULL);
	i++;
	c = 0;
	while (save[i])
		s[c++] = save[i++];
	s[c] = '\0';
	free(save);
	return (s);
}

char *get_next_line(int fd)
{
	char	*buff;
	char	*line;
	static char	*save;
	ssize_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	len = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return(NULL);
	while (!(ft_strchr(save, '\n')) && len != 0)
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[len] = '\0';
		save = ft_strjoin(save, buff);
		// printf("save: [%s], buff: [%s]\n", save, buff);
	}
	free(buff);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	// printf("1save: [%s] line: [%s]\n", save, line);
	// fflush(stdout);
	save = ft_save(save);
	// printf("2. save: [%s] line: [%s]\n", save, line);
	return(line);
}

int	main(void)
{
	int		fd;
	char	*line;

	line = "";
	fd = open("file.txt", O_RDONLY);
	// while( get_next_line(fd))
	// {
	line = get_next_line(fd);
	printf("> %s", line);
	free(line);
	// }
	line = get_next_line(fd);
	printf("> %s", line);
	free(line);
	line = get_next_line(fd);
	printf("> %s", line);
	free(line);
		line = get_next_line(fd);
	printf("> %s", line);
	free(line);
	return (0);
}