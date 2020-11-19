#include "libft.h"

void			*ft_memccpy_mod(void *dest, void *src, int c, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		if (((unsigned char*)src)[i] == (unsigned char)c)
		{
			((unsigned char*)dest)[i] = '\0';
			break ;
		}
		i++;
	}
	if (i < n)
		return (src + i + 1);
	return (NULL);
}

void			free_result(char **remain)
{
	free(*remain);
	*remain = NULL;
}

size_t			ft_realloc(char **line)
{
	char		*temp;
	size_t		index;

	index = ft_strlen(*line);
	if ((temp = malloc(index + 2)) == NULL)
		return (-1);
	ft_memccpy_mod(temp, *line, '\0', index + 1);
	free(*line);
	if ((*line = malloc(index + 2)) == NULL)
	{
		free(temp);
		return (-1);
	}
	ft_memccpy_mod(*line, temp, '\0', index + 1);
	ft_bzero((*line) + index, 2);
	free(temp);
	return (index);
}

int				give_remainder(char **line, char **remain)
{
	ssize_t		index;
	char		*str;
	int			len;

	index = ft_realloc(line);
	if (index == -1)
		return (-1);
	str = ft_memccpy_mod((*line) + index, *remain, '\n', ft_strlen(*remain));
	if (str != NULL)
	{
		len = ft_strlen(str);
		ft_memccpy_mod(*remain, str, '\0', len + 1);
		ft_bzero((*remain) + len, 2 - len);
		return (1);
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int			result;
	char		buffer[1];
	static char	*remain[1024];

	if (fd < 0 || !line || read(fd, buffer, 0) < 0)
		return (-1);
	if ((*line = ft_strdup("")) == NULL)
		return (-1);
	if (remain[fd] != NULL)
	{
		if ((result = give_remainder(line, &remain[fd])) == 1 || result == -1)
			return (result);
	}
	else if ((remain[fd] = malloc(2)) == NULL)
		return (-1);
	while ((result = read(fd, buffer, 1)))
	{
		ft_bzero(buffer + result, 2 - result);
		ft_memccpy_mod(remain[fd], buffer, '\0', ft_strlen(buffer) + 1);
		if ((result = give_remainder(line, &remain[fd])) == 1 || result == -1)
			return (result);
	}
	free_result(&remain[fd]);
	return (0);
}
