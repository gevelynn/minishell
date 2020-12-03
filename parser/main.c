#include "../libft/libft.h"
#include "../minishell.h"

int			counting_quotes(char *str, int one_quotes, int two_quotes, int i)
{
	if(str[i] == '\'')
	{   
		one_quotes++;
		if(two_quotes % 2 || (str[i - 1] == '\\' && one_quotes % 2))
			one_quotes++;
		return (one_quotes);
	}
	else if(str[i] == '\"')
	{
		two_quotes++;
		if(one_quotes % 2 || (str[i - 1] == '\\'))
			two_quotes++;
		return (two_quotes);
	}
	return (0);
}

void		recording_arguments(char *str, t_all *all, int start, int i)
{
	if (str[i] == '|')
		all->data->pipe = 1;
	line_search(str, all, start, i - 1); // обработка одной линии (строки) до разделителя
	all->data->next = p_lstnew();
	if (all->data->pipe)
		all->data->next->pipe_behind = 1;
	all->data = all->data->next;
}

void		parser(char *str, t_all *all)
{
	int		i;
	int		start;
	int		one_quotes;
	int		two_quotes;

	i = -1;
	start = 0;
	one_quotes = 0;
	two_quotes = 0;
	all->data = p_lstnew();
	all->head = all->data;
	while (str[++i]) //поиск разделителя
	{
		if(str[i] == '\'')
			one_quotes = counting_quotes(str, one_quotes, two_quotes, i);
		else if(str[i] == '\"')
			two_quotes = counting_quotes(str, one_quotes, two_quotes, i);
		else if ((str[i] == ';' || str[i] == '|') && !(one_quotes % 2) && !(two_quotes % 2)
				&& str[i - 1] != '\\')
		{
			recording_arguments(str, all, start, i);
			start = i + 1;
		}
	}
	line_search(str, all, start, i - 1); // когда дошли до конца строки, либо если разделителя не было
}

void		start_loop(t_all *all)
{
	char 	*line;

	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	while (get_next_line(0, &line) > 0)
	{
		if (line && (*line))
			parser(line, all);
		all->data = all->head;
		if (execution(all) == 0)
			break ;	
		if (all->child_killed != 1)
			ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
		all->child_killed = 0;
		free (line);
		line = NULL;
		p_lstclear(&(all->head));
		all->child_killed = 0;
	}
	free(line);
	ft_putendl_fd("exit", 1);
}

int			main(int argc, char **argv, char **envp)
{	
	t_all	all;

	all.exit_status = 0;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_c_handler);
	if (argc != 1 || !argv)
	{
		ft_putendl_fd("No parameters needed", 2);
		return (-1);
	}
	envp_saving(envp, &all);
	start_loop(&all);
	return (0);
}

