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
void			syntax_check(t_all **all, char *str, int *arr, t_list **new)
{
	int			i;
	char		*word;
	t_list		*temp;

	i = -1;
	temp = *new;
	if (!(word = (char *)malloc(sizeof(char) * ((arr[1] + 1) - (arr[0]--))))) // почистить
		return (error_malloc());
	while (++arr[0] < arr[1])
		word[++i] = str[arr[0]];
	word[i + 1] = '\0';
	word = search_variable(all, &word);
	if (temp->content == NULL)
		temp->content = word;
	else
		ft_lstadd_back(&temp, ft_lstnew(word));
}


void			arguments_search(char *str, t_all **all)
{
	int			arr[2];
	int			one_quotes;
	int			two_quotes;
	t_list		*new = NULL;

	arr[0] = 0;
	arr[1] = -1;
	one_quotes = 0;
	two_quotes = 0;
	new = ft_lstnew(NULL);
	while (str[++arr[1]])
	{
		// последние два условия для корректной обработки аргументов при экранировании (например, \'\"\\ "\hello\$PWD")
		if (str[arr[1]] == '\'' && str[arr[1] - 1] != '\\') 
			one_quotes++;
		else if (str[arr[1]] == '\"' && str[arr[1] - 1] != '\\')
			two_quotes++;
		else if (str[arr[1]] == ' ' && one_quotes % 2 == 0 && two_quotes % 2 == 0)
		{
			syntax_check(all, str, arr, &new);
			while (str[arr[1]++] == ' ')
				arr[0] = arr[1];
			arr[1] = arr[0] - 1;
		}
	}
	syntax_check(all, str, arr, &new);
	filling_struct(all, new, ft_lstsize(new));
	ft_lstclear(&new, NULL);
}

// строка для обработки
void			line_search(char *line, t_all **all, int start, int end)
{
	char		*str;
	int			j;
	// t_data		*temp; // temporary
	// int			i; // temporary

	// temp = (*all)->data;
	if (end >= start)
	{
		while (line[start] == ' ') // убрали пробелы в начале строки
			start++;
		while (line[end] == ' ')
			end--;
		if (line[end] != ' ')
			end++;
		if (!(str = (char *)malloc(sizeof(char) * ((end + 1) - (start--))))) // почистить
			return (error_malloc());
		j = -1;
		while (++start < end)
			str[++j] = line[start];
		str[j + 1] = '\0';
		arguments_search(str, all);
	// 	while (temp)
	// 	{
	// 		printf("|New string|\n");
	// 		i = 0;
	// 		while (temp->args[i])
	// 		{
	// 			printf("%s\n", temp->args[i]);
	// 			i++;
	// 		}
	// 		printf("%d\n", temp->pipe);
	// 		printf("%d\n", temp->pipe_behind);
	// 		printf("%d\n", temp->red_to);
	// 		printf("%d\n", temp->doub_red_to);
	// 		printf("%d\n", temp->red_from);
	// 		temp = temp->next;
	// 	}
	// 	free(str);
	}
}