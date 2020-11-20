#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// // сдвиг строки на один символ
// void line_shift(char **str, int j)
// {
// 	while((*str)[++j])
// 		(*str)[j] = (*str)[j + 1];
// }

// int delete_symbol(char **str, int i, char c)
// {
// 	int j;

// 	j = i;
// 	line_shift(str, (i - 1));
// 	while ((*str)[j] != c && ((*str)[j]))
// 		j++;
// 	if ((*str)[j] != c)
// 		(*str)[j] = c;
// 	line_shift(str, (j - 1));
// 	return (j);
// }

// // убираем кавычки, согласно синтаксису bash
// void	syntax_check(char **str)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while ((*str)[i])
// 	{
// 		if ((*str)[i] == '\'' || (*str)[i] == '\"')
// 		{
// 			if ((*str)[i] == '\'')
// 				j = delete_symbol(str, i, '\'');
// 			else
// 				j = delete_symbol(str, i, '\"');
// 			i = j;
// 		}
// 		else
// 			i++;
// 	}
// }

// // Поиск команды
// int	command_search(char *str)
// {
// 	int	i;
// 	int j;
// 	int start;
// 	char *word;

// 	i = 0;
// 	while (str[i] == ' ')
// 		i++;
// 	start = i;
// 	while (str[i] != ' ' && (str[i]))
// 		i++;
// 	if (!(word = (char *)malloc(sizeof(char) * (i - start--)))) // не забудь подчистить за собой
// 		return (-1);
// 	j = -1;
// 	while (++start < i)
// 		word[++j] = str[start];
// 	word[j + 1] = '\0';
// 	syntax_check(&word);
// 	printf("%s\n", word);
// 	return (0);
// }

// int parser(char **str)
// {
// 	if ((command_search(*str) != 0))
// 		return (-1);
// 	return (1);
// }

// int		main()
// {	
// 	int		check;
// 	char 	*line;

// 	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
// 	while (get_next_line(0, &line) > 0)
// 	{
// 		if (!(check = parser(&line)))
// 			write(1, "wrong command\n", 15);
// 		// printf("%s\n", line);
// 		ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
// 		free (line);
// 	}
// 	free (line);
// 	return (0);
// }

int main()
{
	int i = 0;
	int fd = open("test.txt", O_RDONLY);
	char *line = NULL;
	t_data *content = NULL;
	t_data *tmp;
	content = p_lstnew();
	tmp = content;

	// i = get_next_line(fd, &line);
	// content->file_name = line;
	while (get_next_line(fd, &line))
	{
		p_lstadd_back(&content, p_lstnew());
		content->file_name = line;
		content->pipe = i + 1;
		content->red_to = i + 2;
		content->doub_red_to = i + 3;
		content->red_from = i + 4;
		content = content->next;
		i++;
		line = NULL;
	}
	while (tmp->next)
	{
		printf("%s\n", tmp->file_name);
		tmp = tmp->next;
	}

	return(0);
}












