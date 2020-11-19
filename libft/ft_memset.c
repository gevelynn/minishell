#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	while (n > 0)
		((unsigned char*)s)[--n] = (unsigned char)c;
	return (s);
}
