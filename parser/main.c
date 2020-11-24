#include "../libft/libft.h"
#include "../minishell.h"

void			check_flags(char *str, t_data **temp, int i)
{
	if (str[i] == '|')
		(*temp)->pipe = 1;
	else if (str[i] == '<')
		(*temp)->red_from = 1;
	else if (str[i] == '>' && str[i + 1] != '>')
		(*temp)->red_to = 1;
	else if (str[i] == '>' && str[i + 1] == '>')
		(*temp)->doub_red_to = 1;
	else
		;
	(*temp)->next = p_lstnew();
	*temp = (*temp)->next;
}

void				parser(char **str, t_data **elem)
{
	int			i;
	int			start;
	int			one_quotes;
	int			two_quotes;
	t_data		*temp;

	i = -1;
	start = 0;
	one_quotes = 0;
	two_quotes = 0;
	temp = *elem;  // coхранили голову
	while ((*str)[++i]) //поиск разделителя
	{
		if ((*str)[i] == '\'')
			one_quotes++;
		else if ((*str)[i] == '\"')
			two_quotes++;
		else if (((*str)[i] == ';' || (*str)[i] == '|' || (*str)[i] == '<' || (*str)[i] == '>') &&
				(one_quotes % 2 == 0 && two_quotes % 2 == 0))
		{
			check_flags(*str, &temp, i); // установка флагов под разделители
			line_search(*str, elem, start, i); // обработка одной линии (строки) до разделителя
			if ((*str)[i] == '>' && (*str)[i + 1] == '>')
				i++;
			start = i + 1;
		}
	}
	line_search(*str, elem, start, i); // когда дошли до конца строки, либо если разделителя не было
}

int				main()
{	
	char 		*line;
	t_data		*elem;

	elem = p_lstnew();
	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	while (get_next_line(0, &line) > 0)
	{
		parser(&line, &elem);
		ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
		free (line);
	}
	free (line);
	return (0);
}











