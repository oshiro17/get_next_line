#include "get_next_line.h"

char	*ft_get_line(char *save)
{
	int		i;
	char	*to_line;

	if (!save[0])
		return (NULL);
	to_line = (char *)malloc(sizeof(char) * ((ft_strlen(save, '\n')) + 1));
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
	s = (char *)malloc(sizeof(char) * (ft_strlen(save, '\0') - i + 1));
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
char	*buff_to_save(char *save, int fd)
{
	ssize_t	len;
	char		*buff;

	len = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return(NULL);
	//'\n'がないときに入る
	while (!(ft_strchr(save,'\n')) && len > 0)
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
		{	
			free (buff);
			return(NULL);
		}
		buff[len] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return(save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[256];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 255)
		return (0);
//	len = 1;
	// buff = malloc(BUFFER_SIZE + 1);
	// if (!buff)
	// 	return (NULL);
	// while (!(ft_strchr(save[fd], '\n')) && len > 0)
	// {
	// 	len = read(fd, buff, BUFFER_SIZE);
	// 	if (len == -1)
	// 	{
	// 		free(buff);
	// 		return (NULL);
	// 	}
	// 	buff[len] = '\0';
	// 	save[fd] = ft_strjoin(save[fd], buff);
	// }
	// free(buff);
	save[fd] = buff_to_save(save[fd], fd);
	if (!save[fd])
		return (NULL);
	line = ft_get_line(save[fd]);
	save[fd] = ft_save(save[fd]);
	return (line);
}
