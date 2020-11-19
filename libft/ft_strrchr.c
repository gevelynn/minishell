#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	while (*s != c)
	{
		if (i == 0)
			return (NULL);
		s--;
		i--;
	}
	return ((char *)s);
}
