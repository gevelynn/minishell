#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*array;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	array = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!array)
		return (NULL);
	while (s[i] != '\0')
	{
		array[i] = f(i, s[i]);
		i++;
	}
	array[i] = '\0';
	return (array);
}
