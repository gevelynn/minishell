#include "../libft/libft.h"
#include "../minishell.h"

// убираем кавычки, согласно синтаксису bash
void			syntax_check(t_all *all, char *str, int *arr, t_list **new)
{
	int			i;
	char		*word;
	t_list		*temp;

	i = -1;
	temp = *new;
	if (!(word = ft_calloc((arr[1] + 1) - arr[0], sizeof(char)))) // почистить
		return (error_malloc());
	word = search_variable(all, &word, str, arr);
	if (temp->content == NULL)
		temp->content = word;
	else
		ft_lstadd_back(&temp, ft_lstnew(word));
}


void			arguments_search(char *str, t_all *all)
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
		if(str[arr[1]] == '\'')
			one_quotes = counting_quotes(str, one_quotes, two_quotes, arr[1]);
		else if(str[arr[1]] == '\"')
			two_quotes = counting_quotes(str, one_quotes, two_quotes, arr[1]);
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
void			line_search(char *line, t_all *all, int start, int end)
{
	char		*str;
	int			j;
	// t_data		*temp; // temporary
	// int			i; // temporary

	// temp = all->data;
	if (start <= end)
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
		// while (temp)
		// {
		// 	printf("|New string|\n");
		// 	i = 0;
		// 	while (temp->args[i])
		// 	{
		// 		printf("|%s|\n", temp->args[i]);
		// 		i++;
		// 	}
		// 	printf("%d\n", temp->pipe);
		// 	printf("%d\n", temp->pipe_behind);
		// 	printf("%d\n", temp->red_to);
		// 	printf("%d\n", temp->doub_red_to);
		// 	printf("%d\n", temp->red_from);
		// 	temp = temp->next;
		// }
		free(str);
	}
}
