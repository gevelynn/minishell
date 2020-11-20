#include "parser.h"
#include <stdio.h>

int command_search(char *str)
{
	int	i;
	int j;
	int start;
	char *word;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	start = i;
	while (str[i] != ' ' || str[i] == '\t' || !(str[i]))
		i++;
	word = (char *)malloc(sizeof(char) * (i - start--)); // не забудь подчистить за собой
	j = -1;
	while (++start < i)
		word[++j] = str[start];
	return (1);
}

int parser(char **str)
{
	if (!(command_search(*str)))
		return (-1);
	return (1);
}

int		main()
{	
	int		check;
	char 	*line;

	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	while (get_next_line(0, &line) > 0)
	{
		if (!(check = parser(&line)))
			write(1, "wrong command\n", 15);
		// printf("%s\n", line);
		ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
		free (line);
	}
	free (line);
	return (0);
}

