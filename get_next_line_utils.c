#include "get_next_line.h"

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