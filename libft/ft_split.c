#include "libft.h"

static size_t		quantity_words(char const *str, char c)
{
	size_t			i;
	size_t			word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
			word++;
		while (str[i] != c && str[i])
			i++;
	}
	return (word);
}

static size_t		len_words(char const *str, char c)
{
	size_t			len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	return (len);
}

static char			**free_array(char **array, size_t i)
{
	while (i > 0)
		free(array[--i]);
	free(array);
	return (array);
}

char				**ft_split(char const *s, char c)
{
	char			**array;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!(array = (char **)malloc(sizeof(char *) * (quantity_words(s, c) + 1))))
		return (NULL);
	while (i < quantity_words(s, c))
	{
		while (s[j] == c && s[j])
			j++;
		array[i] = ft_substr(&s[j], 0, len_words(&s[j], c));
		if (!array[i])
		{
			free_array(array, i);
			return (NULL);
		}
		j += len_words(&s[j], c);
		i++;
	}
	array[i] = NULL;
	return (array);
}
