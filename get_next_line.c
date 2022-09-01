#include "get_next_line.h"

char	*ft_get_line(char *save)
{
	int		i;
	char	*to_line;

	ft_strlen(save,'\n');
	printf("[test]\n");
	fflush(stdout);
	ft_strlen(save,'\n');
	if (!save[0])
		return (NULL);
	to_line = (char *)malloc(sizeof(char) * ((ft_strlen(save,'\n')) + 1));

	printf("[hi]\n");
	fflush(stdout);
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
	static char	*save[256];
	ssize_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 255)
		return (0);
	len = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return(NULL);
	while (!(ft_strchr(save[fd], '\n')) && len > 0)
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[len] = '\0';
		save[fd] = ft_strjoin(save[fd], buff);
		printf("save: [%s], buff: [%s]\n", save[fd], buff);
		if(*buff == '\0')
			break;
		fflush(stdout);
	}
	free(buff);
	if (!save[fd])
		return (NULL);
	line = ft_get_line(save[fd]);
	// printf("1save: [%s] line: [%s]\n", save, line);
	// fflush(stdout);
	save[fd] = ft_save(save[fd]);
	// printf("2. save: [%s] line: [%s]\n", save, line);
	return(line);
}

int	main(void)
{
	int		fd;
	char	*line;
	line = "";
	fd = open("file.txt", O_RDONLY);
	printf("%d",fd);

	while(line)
	{
		line = get_next_line(fd);
		if (line)
			printf("> %s", line);
		free(line);
	}
	free(line);
	return (0);
}