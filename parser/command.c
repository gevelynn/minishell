#include "../libft/libft.h"
#include "../minishell.h"

// сдвиг строки на один символ
void line_shift(char **str, int j)
{
	while((*str)[++j])
		(*str)[j] = (*str)[j + 1];
}

int delete_symbol(char **str, int i, char c)
{
	int flag;

	flag = 0;
	if (c == '\"') // для экранирования специальных символом $\"
		flag = 1;
	if (c == '\\')
		line_shift(str, ((i++) - 1));
	else
	{
		line_shift(str, (i - 1));
		while ((*str)[i] != c && ((*str)[i]))
		{
			if (flag == 1 && (*str)[i] == '\\' && ((*str)[i + 1] == '$' ||
				(*str)[i + 1] == '\\' || (*str)[i + 1] == '\"'))
				line_shift(str, (i - 1));
			i++;
		}
		if ((*str)[i] != c)
			(*str)[i] = c;
		line_shift(str, (i - 1));
	}
	return (i);
}

// убираем кавычки, согласно синтаксису bash
void	syntax_check(char **str)
{
	int i;
	int j;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"' || (*str)[i] == '\\')
		{
			j = delete_symbol(str, i, (*str)[i]);
			i = j;
		}
		else
			i++;
	}
}

// Поиск команды
int	command_search(char *str, t_data **elem, int begin, int end)
{
	int	i;
	int j;
	int start;
	char *word;

	i = 0;
	while (str[i] == ' ')
		i++;
	start = i;
	while ((str[i]) && (str[i]) != ' ')
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i - (start--))))) // не забудь подчистить за собой
		return (-1);
	j = -1;
	while (++start < i)
		word[++j] = str[start];
	word[j + 1] = '\0';
	syntax_check(&word);
	printf("%s\n", word);
	return (0);
}