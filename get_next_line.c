/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noshiro <noshiro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 06:14:33 by noshiro           #+#    #+#             */
/*   Updated: 2022/09/09 23:56:36 by noshiro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *save, char *to_line)
{
	int		i;
	char	*to_line;

	// if (!save[0])
	// 	return (NULL);
	// if (ft_strchr(save, '\n'))
	// 	to_line = (char *)malloc(ft_strchr(save, '\n') - save + 2);
	// else
	// 	to_line = (char *)malloc(ft_strlen(save) + 1);
	// if (!to_line)
	// 	return (NULL);
	i = 0;
	// save == null
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
	s = (char *)malloc(ft_strlen(save) - i + 1);
	if (!s)
	{
		free(save);
		return (NULL);
	}
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
	char	*buff;

	len = 1;
	buff = malloc(BUFFER_SIZE + 1UL);
	if (!buff)
		return (NULL);
	while (!(ft_strchr(save, '\n')) && len > 0)
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
		{	
			free (buff);
			return (NULL);
		}
		buff[len] = '\0';
		save = ft_strjoin(save, buff);
		if (!save)
			break;
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[256];
	char		*to_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 255)
		return (NULL);
	save[fd] = buff_to_save(save[fd], fd);
	if (!save[fd])
		return (NULL);
	if (!save[fd][0])
		return (NULL);
	if (ft_strchr(save[fd], '\n'))
		to_line = (char *)malloc(ft_strchr(save[fd], '\n') - save + 2);
	else
		to_line = (char *)malloc(ft_strlen(save[fd]) + 1);
	if (!to_line)
	{
		free(save[fd]);
		return (NULL);
	}
	line = ft_get_line(save[fd]);
	// if (!line)
	// {
	// 	free(save);
	// 	return(NULL);
	// }
	save[fd] = ft_save(save[fd]);
	return (line);
}

// int main(void)
// {
// 	int fd ;
// 	char *line;

// 	fd = open("file.txt",O_RDONLY);
// 	while(line)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s",line);
// 		free(line);
// 	}
// 	return(0);
// }
