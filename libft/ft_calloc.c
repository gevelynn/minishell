#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	i;

	i = 0;
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	while (i < nmemb * size)
	{
		((char *)array)[i] = '\0';
		i++;
	}
	return (array);
}
