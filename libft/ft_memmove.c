#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (dest == src)
		return (dest);
	if ((unsigned char*)dest > (unsigned char*)src)
	{
		while (n-- > 0)
			((unsigned char*)dest)[n] = ((unsigned char *)src)[n];
	}
	else
	{
		while (i < n)
		{
			((unsigned char*)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
