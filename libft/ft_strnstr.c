#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	if (little[i] == 0)
		return ((char *)big);
	if (big && ft_strlen(little) > len)
		return (NULL);
	while (big[i] != '\0' && i < len)
	{
		k = 0;
		if (big[i] == little[k])
		{
			j = i;
			while (big[++j] == little[++k] && little[k] != '\0' && j < len)
				;
			if (little[k] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
