#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		nb;
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
		{
			nb = ((unsigned char*)s1)[i] - ((unsigned char*)s2)[i];
			return (nb);
		}
		i++;
	}
	return (0);
}
