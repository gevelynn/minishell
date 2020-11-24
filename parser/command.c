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
void			syntax_check(char *str, t_data **elem, int start, int end)
{
	int			i;
	int			j;
	char		*word;

	i = -1;
	word = (char *)malloc(sizeof(char) * ((end + 1) - (start--))); // почистить
	while (++start < end)
		word[++i] = str[start];
	word[i + 1] = '\0';
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"' || word[i] == '\\')
		{
			j = delete_symbol(&word, i, word[i]);
			i = j;
		}
		else
			i++;
	}
	printf("|%s|\n", word);
	// state = end + 1;
}


void			arguments_search(char **str, t_data **elem)
{
	int			i;
	int			start;
	int			one_quotes;
	int			two_quotes;

	i = -1;
	start = 0;
	one_quotes = 0;
	two_quotes = 0;
	while ((*str)[++i])
	{
		// последние два условия для корректной обработки аргументов при экранировании (например, \'\"\\ "\hello\$PWD")
		if ((*str)[i] == '\'' && (*str)[i - 1] != '\\') 
			one_quotes++;
		else if ((*str)[i] == '\"' && (*str)[i - 1] != '\\')
			two_quotes++;
		else if ((*str)[i] == ' ' && one_quotes % 2 == 0 && two_quotes % 2 == 0)
		{
			syntax_check(*str, elem, start, i);
			while ((*str)[i++] == ' ')
				start = i;
			i = start - 1;
		}
	}
	syntax_check(*str, elem, start, i);
}

// строка для обработки
void			line_search(char *line, t_data **elem, int start, int end)
{
	char		*str;
	int			j;

	if (end >= start)
	{
		while (line[start] == ' ') // убрали пробелы в начале строки
			start++;
		while (line[end] == ' ')
			end--;
		if (line[end] != ' ')
			end++;
		str = (char *)malloc(sizeof(char) * ((end + 1) - (start--))); // почистить
		j = -1;
		while (++start < end)
			str[++j] = line[start];
		str[j + 1] = '\0';
		arguments_search(&str, elem);
		free(str);
	}
}