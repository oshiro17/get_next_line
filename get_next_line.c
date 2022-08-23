#include "get_next_line.h"
#include <string.h>

size_t	ft_strlen(const char *s, char escape)
{
	size_t	i;

	i = 0;
	if (!s || !escape)
		return(i);
	while (s[i] != escape)
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	char	*nstr;
	size_t		length;

	i = 0;
	if ((s1 == NULL) && (s2 == NULL))
		return (NULL);
	length = ft_strlen((char *)s1, '\0') + ft_strlen((char *)s2, '\0');
	nstr = (char *)malloc(sizeof(char) * (length + 1));
	if (!nstr)
		return (NULL);
	while (*s1 && i < length)
	{
		nstr[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 && i < length)
	{
		nstr[i] = *s2;
		s2++;
		i++;
	}
	nstr[length] = '\0';
	return (nstr);
}

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

	abond_len = ft_strlen(to_save,'\0');
	if(!to_save[abond_len])
	{
		free(save);
		return(NULL);
	}
	save = malloc((ft_strlen(save,'\0')) - abond_len + 1);
	if (!save)
		return(NULL);
	abond_len++;
	i = 0;
	while (to_save[abond_len])
		save[i] = to_save[abond_len];
	free(to_save);
	return(save);
}

char *get_next_line(int fd)
{
	char	*buff;
	char	*line;
	static char	*save;
	ssize_t		len;

	len = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return(NULL);
	printf("111");fflush(stdout);
	while ((ft_strchr(save, '\n')) == NULL && len != 0)
	{
		printf("whileはいったぜ");fflush(stdout);
		len = read(fd, buff, BUFFER_SIZE);
		printf("115");fflush(stdout);
		buff[len] = '\0';
		save = ft_strjoin(save, buff); 
	}
	printf("118");fflush(stdout);
	free(buff);
	line = ft_get_line(save);
	save = ft_save(save);
	return(save);
}

int main(void)
{
	char *line;
	int fd;

	printf("aaaa");fflush(stdout);
	//fd = open("./gnl_instructions.txt", O_RDONLY);
	//fd = open("./file.txt", O_RDONLY);
	//fd = open("./num_even.txt", O_RDONLY);
	fd = open("file.txt", O_RDONLY);
	//fd = open("./41_with_nl", O_RDONLY);
	//fd = open("./43_no_nl", O_RDONLY);
	//line = ft_substr("", 0, 0);
	//while (line)
	//{
	//	line = get_next_line(fd);
	//	printf("line : %s", line); 
	//	free (line);
	//}
	//line = get_next_line(1000);
	//printf("line : %s", line); 
	//free (line);
	//line = get_next_line(-1);
	//printf("line : %s", line); 
	//free (line);
	line = get_next_line(fd);
	printf("line : %s", line); 
	free (line);
	line = get_next_line(fd);
	printf("line : %s", line); 
	free (line);
	line = get_next_line(fd);
	printf("line : %s", line); 
	free (line);
	line = get_next_line(fd);
	printf("line : %s", line); 
	free (line);
	line = get_next_line(fd);
	printf("line : %s", line); 
	free (line);
	line = get_next_line(fd);
	printf("line : %s", line); 
	free (line);
	line = get_next_line(fd);
	printf("line : %s", line); 
	free (line);
	line = get_next_line(fd);
	printf("line : %s", line); 
	free (line);
	line = get_next_line(fd);
	printf("line : %s", line); 
	free (line);
	return 0;
}