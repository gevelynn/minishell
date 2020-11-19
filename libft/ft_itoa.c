#include "libft.h"

static size_t	len_number(long int n)
{
	size_t		len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char		*result_number(char *s, size_t len_n, long int nb)
{
	while (nb > 0)
	{
		if (nb / 10 == 0)
		{
			s[--len_n] = nb + '0';
			nb = nb / 10;
		}
		else
		{
			s[--len_n] = (nb % 10) + '0';
			nb = nb / 10;
		}
	}
	return (s);
}

char			*ft_itoa(int n)
{
	char		*str;
	size_t		len_nb;
	long int	num;

	num = n;
	len_nb = (size_t)len_number(num);
	str = (char *)malloc(sizeof(char) * (len_nb + 1));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	str[len_nb] = '\0';
	if (num == 0)
		str[--len_nb] = '0';
	str = result_number(str, len_nb, num);
	return (str);
}
