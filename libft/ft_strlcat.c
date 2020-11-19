#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = len_dst;
	while (*src != '\0' && i + 1 < size)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
	if (size <= len_dst)
		return (size + len_src);
	return (len_dst + len_src);
}
