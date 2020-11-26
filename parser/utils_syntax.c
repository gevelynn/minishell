#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

int		check_dollar(t_all **all, char **word, int i)
{
	int		start;
	int		len;
	char	*tmp;
	char 	ch;
	char	*tempory; //временная

	// printf("%s\n", (*word));
	start = i++; // начало переменной (место $)
	while ((*word)[i] && (*word)[i] != '\'' && (*word)[i] != '\"' && (*word)[i] != ' ')
		i++; // конец переменной
	ch = (*word)[i]; // сохранили символ конца переменной
	(*word)[i] = '\0'; // заменили на символ конца строки, что узнать длину переменной окружения
	len = ft_strlen(get_env_str(((*word) + (start + 1)), *all));
	tmp = ft_strdup((*word)); //сохранили слово
	free((*word));
	(*word) = ft_calloc(ft_strlen(tmp) + len - (i - start), sizeof(char)); // выделили новую память с учетом переменной окружения
	len = -1; // больше не нужна, можно использовать
	while(++len < start)
		(*word)[len] = tmp[len]; // копируем строку обратно в (*word) до знака $
	// после того как дошли до доллара, то вместо названия переменной окружения добавали путь
	tempory = get_env_str((tmp + (start + 1)), *all);
	ft_strlcat((*word), tempory, ft_strlen(tempory) + ft_strlen(*word) + 1);
	len = ft_strlen((*word));
	(*word)[start + len] = ch; // вернули сохраненый символ строка 14;
	start = i;
	while (tmp[++start])
		(*word)[len++] = tmp[start];
	return (i);
}

char		*search_variable(t_all **all, char **word)
{
	int		i;
	int		one_quotes;

	i = 0;
	one_quotes = 0;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'' || (*word)[i] == '\"' || (*word)[i] == '\\')
		{
			if ((*word)[i] == '\'')
				one_quotes++;
			i = delete_symbol(&(*word), i, (*word)[i], all);\
		}
		else if ((*word)[i] == '$' && one_quotes % 2 == 0 && (*word)[i - 1] != '\\' &&
				(ft_isalnum((*word)[i + 1]) || (*word)[i + 1] == '_'))
		// {
		// 	printf("GOOD\n");
		// 	printf("%s\n", (*word));
		// 	printf("%d\n", i);
			i = check_dollar(all, &(*word), i); //функция должна вернуть int (то есть с какого места продолжаем парсить строку)
		// }
		else
			i++;
	}
	return ((*word));
}