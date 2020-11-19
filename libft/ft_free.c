#include "libft.h"

int		ft_free(char **array, int a)
{
	free(*array);
	*array = NULL;
	return (a);
}
