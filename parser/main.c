#include "../libft/libft.h"
#include "../minishell.h"
// #include <unistd.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

int parser(char **str, t_data **elem)
{
	int i;
	int start;
	int one_quotes;
	int two_quotes;

	i = 0;
	start = 0;
	one_quotes = 0;
	two_quotes = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
			one_quotes++;
		else if ((*str)[i] == '\"')
			two_quotes++;
		else if (((*str)[i] == ';' || (*str)[i] == '|' || (*str)[i] == '<' || (*str)[i] == '>') &&
				(one_quotes % 2 == 0 && two_quotes % 2 == 0))
		{
			printf("YPCcc\n");
			// command_search(*str, elem, start, i);
			start = i;
		}
		i++;
	}
	if (start == 0)
		command_search(*str, elem, 0, 0);
	// if ((command_search(*str) != 0))
	// 	return (-1);
	// printf("line: %s\n", *str);
	return (1);
}

int		main()
{	
	int		check;
	char 	*line;
	t_data	*elem;

	elem = p_lstnew();
	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	while (get_next_line(0, &line) > 0)
	{
		if (!(check = parser(&line, &elem)))
			write(1, "wrong command\n", 15);
		ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
		free (line);
	}
	free (line);
	return (0);
}

// int main()
// {
// 	int i = 0;
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line = NULL;
// 	t_data *content = NULL;
// 	t_data *tmp;
// 	content = p_lstnew();
// 	tmp = content;

// 	// i = get_next_line(fd, &line);
// 	// content->file_name = line;
// 	while (get_next_line(fd, &line))
// 	{
// 		// printf("%s\n", line);
// 		p_lstadd_back(&content, p_lstnew());
// 		content->file_name = line;
// 		content->pipe = i + 1;
// 		content->red_to = i + 2;
// 		content->doub_red_to = i + 3;
// 		content->red_from = i + 4;
// 		content = content->next;
// 		i++;
// 		line = NULL;
// 	}
// 	// printf("%d\n", i);
// 	// printf("%d\n", p_lstsize(tmp));
// 	content = tmp;
// 	while (tmp->next)
// 	{
// 		printf("%s\n", tmp->file_name);
// 		tmp = tmp->next;
// 	}
// 	// printf("%s\n", tmp->file_name);
// 	return(0);
// }












