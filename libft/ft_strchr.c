#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s_cpy;
	char	c_cpy;

	i = 0;
	s_cpy = (char*)s;
	c_cpy = (char)c;
	while (s_cpy[i])
	{
		if (s_cpy[i] == c_cpy)
			return (&(s_cpy[i]));
		i++;
	}
	if (s_cpy[i] == c_cpy)
		return (&(s_cpy)[i]);
	return (NULL);
}
