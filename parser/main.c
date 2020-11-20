#include "parser.h"
#include <stdio.h>

// сдвиг строки на один символ
void line_shift(char **str, int j)
{
	// j = i - 1;
	while((*str)[++j])
		(*str)[j] = (*str)[j + 1];
}

// убираем двойные кавычки
// void	double_quotes(char **str)
// {
// 	int i;

// 	i = 0;
// 	while ((*str)[i])
// 	{
// 		if (((*str)[i] == '\'' && (*str)[i + 1] == '\'') ||
// 			((*str)[i] == '\"' && (*str)[i + 1] == '\"'))
// 		{
// 			line_shift(str, (i - 1));
// 			line_shift(str, (i - 1));
// 		}
// 		else
// 			i++;
// 	}
// }


// убираем кавычки, согласно синтаксису bash
void	syntax_check(char **str)
{
	int i;
	int j;

	// double_quotes(str);
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			if ((*str)[i] == '\'')
			{
				j = i;
				line_shift(str, (i - 1));
				while ((*str)[j] != '\'')
					j++;
				line_shift(str, (j - 1));
			}
			else
			{
				j = i;
				line_shift(str, (i - 1));
				while ((*str)[j] != '\"')
					j++;
				line_shift(str, (j - 1));
			}
			i = j;
		}
		else
			i++;
	}
}

// Поиск команды
int	command_search(char *str)
{
	int	i;
	int j;
	int start;
	char *word;

	i = 0;
	while (str[i] == ' ')
		i++;
	start = i;
	while (str[i] != ' ' && (str[i]))
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i - start--)))) // не забудь подчистить за собой
		return (-1);
	j = -1;
	while (++start < i)
		word[++j] = str[start];
	word[j + 1] = '\0';
	syntax_check(&word);
	printf("%s\n", word);
	return (0);
}

int parser(char **str)
{
	if ((command_search(*str) != 0))
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

