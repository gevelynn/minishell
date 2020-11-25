#include "../libft/libft.h"
#include "../minishell.h"

void free_array(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int add_string(t_data **elem, char **str, int len)
{
	int i;
	char **temp;

	i = -1;
	if (!(temp = (char **)malloc(sizeof(char *) * len)))
		return (0);
	while (++i < len)
	{
		if (!(temp[i] = (char *)malloc(sizeof(char) * ft_strlen((*elem)->argv[i]))))
			return (0);
		temp[i] = (*elem)->argv[i];
	}
	temp[i] = NULL;
	free_array((*elem)->argv);
	i = -1;
	if (!((*elem)->argv = (char **)malloc(sizeof(char *) * (len + 1))))
		return (0);
	while (++i < len)
	{
		if (!((*elem)->argv[i] = (char *)malloc(sizeof(char) * ft_strlen(temp[i]))))
			return (0);
		(*elem)->argv[i] = temp[i];
	}
	if (!((*elem)->argv[i] = (char *)malloc(sizeof(char) * ft_strlen(*str))))
		return (0);
	(*elem)->argv[i] = *str;
	(*elem)->argv[i + 1] = NULL;
	return (1);
}

int malloc_array(t_data **elem, char **str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (!((*elem)->argv))
	{
		if (!((*elem)->argv = (char **)malloc(sizeof(char *) * 2)) || // защитить
			!((*elem)->argv[0] = (char *)malloc(sizeof(char) * ft_strlen(*str))))
			return (0);
		(*elem)->argv[0] = *str;
		(*elem)->argv[1] = NULL;
	}
	else
	{
		while ((*elem)->argv[len])
			len++;
		if (!(add_string(elem, str, len)))
			return (0);
	}
	return (1);
}