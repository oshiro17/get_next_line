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
// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t		i;
// 	char	*nstr;
// 	size_t		length;

// 	printf("22");fflush(stdout);
// 	i = 0;
// 	if ((s1 == NULL) && (s2 == NULL))
// 		return (NULL);
// 	length = ft_strlen((char *)s1, '\0') + ft_strlen((char *)s2, '\0');
// 	nstr = (char *)malloc(sizeof(char) * (length + 1));
// 	if (!nstr)
// 		return (NULL);
// 	printf("30dayo");fflush(stdout);
// 	if (*s1=! '\0' && i < ft_strlen((char *)s1, '\0'))
// 	{
// 		printf("%c",*s1);
// 		fflush(stdout);
// 		// nstr[i] = *s1;
// 		// s1++;
// 		// i++;
// 	}
// 	printf("37");fflush(stdout);
// 	while (*s2 =! ''&& i < ft_strlen((char *)s2, '\0'))
// 	{
// 		nstr[i] = *s2;
// 		s2++;
// 		i++;
// 	}
// 	nstr[length] = '\0';
// 	return (nstr);
// }

// static char	*ft_strrchr(char *line, char c)
// {
// 	int		i;

// 	while (*line && line)
// 	{
// 		if (*line == c)
// 			return (line);
// 		line++;
// 	}
// 	return (NULL);
// }

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
	char	*to_line;
	int		i;

	i = 0;
	to_line = (char *)malloc(ft_strlen(save, '\n') + 2);
	if (!to_line)
		return (NULL);
	while (save[i] != '\n')
	{	
		to_line[i] = save[i];
		i++;
	}
	to_line[i] = '\n';
	to_line[i + 1] = '\0';
	return (to_line);
}

char	*ft_save(char *to_save)
{
	size_t	abond_len;
	int 	i;
	char	*save;

	if(!to_save)
		return(NULL);
	abond_len = ft_strlen(to_save,'\n');
	save = malloc((ft_strlen(to_save,'\0')) - abond_len + 1);
	// printf("ft_save save[%s]to_save[%d]\n",save,to_save[0]);
	if (!save)
		return(NULL);
	abond_len++;
	i = 0;
	while (to_save[abond_len + i])
	{
		save[i] = to_save[abond_len + i];
		i++;
	}
	save[i] = '\0';
	// printf("ft_save save[%s]to_save[%d]\n",save,to_save[0]);
	free(to_save);
	return(save);
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
	printf("1save: [%s] line: [%s]\n", save, line);
	fflush(stdout);
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
	while (line)
	{
		line = get_next_line(fd);
		printf("> %s", line);
		free(line);
	}
	return (0);
}