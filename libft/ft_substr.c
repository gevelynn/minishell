#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	length;
	char	*array;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	length = ft_strlen(s + start);
	if (length < len)
		len = length;
	array = (char *)malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	while (i < len)
	{
		array[i] = s[start];
		i++;
		start++;
	}
	array[i] = '\0';
	return (array);
}
