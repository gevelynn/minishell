#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t		i;
	int			otr;
	long int	res;

	i = 0;
	otr = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		otr = otr * (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (otr == 1 && (res > (res * otr) * 10 + (str[i] - '0')))
			return (-1);
		if (otr == -1 && (res * otr) < otr * (res * 10 + (str[i] - '0')))
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * otr);
}
