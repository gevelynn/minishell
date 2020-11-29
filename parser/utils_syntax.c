#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

int         check_dollar(t_all *all, char **word, int start)
{
    int     len;
    char    *tmp;
    char    *tempory = NULL; //временная

    tmp = ft_strdup((*word)); //сохранили слово
    if (!(tempory = get_env_str(((*word) + start), all)))
        tempory = ft_strdup(""); //почистить
    len = ft_strlen(tempory);
    free(*word);
    (*word) = ft_calloc(ft_strlen(tmp) + len + 1, sizeof(char)); // выделили новую память с учетом переменной окружения
    len = -1;
    while(++len < start)
        (*word)[len] = tmp[len]; // копируем строку обратно в (*word) до знака $
        // после того как дошли до доллара, то вместо названия переменной окружения добавали путь
    ft_strlcat((*word), tempory, ft_strlen(tempory) + ft_strlen(*word) + 1);
    if (tempory[0] == '\0')
        free(tempory);
    len = ft_strlen((*word));
    return (len);
}

char        *search_variable(t_all *all, char **word, char *str, int *arr)
{
    int     i;
    int     start; // для str
    int     end;
    int     one_quotes;
    int     two_quotes;
    int     check;  // для переменной окружения
    int     num;  // для обработки $1234 вот такого случая с оригинальным bash

    i = 0;
    start = arr[0];
    end = arr[1];
    one_quotes = 0;
    two_quotes = 0;

    while (start < end)
    {
        //------------------------------------------------------------
        if (str[start] == '$' && !(one_quotes % 2) && (ft_isalnum(str[start + 1]) || str[start + 1] == '_'))
        {
            num = start;
            check = i; //запомнили место куда будет переписана переменная окружения в word
            start++;
            while (str[start] && str[start] != '\'' && str[start] != '\"' && str[start] != ' ' &&
                str[start] != '$' && str[start] != '\\')
            {
                if (str[num] == '$' && ft_isdigit(str[num + 1]) && ft_isdigit(str[num + 2]))
                {
                    (*word)[i] = str[start];
                    (*word)[i++] = str[start++];
                    break ;
                }
                (*word)[i] = str[start];
                start++;
                i++;
            }
            i = check_dollar(all, word, check); //возвращает длину строки word  с подставленной переменной окружения
            start--;
            i--;
        }
        //------------------------------------------------------------
        else if (str[start] == '\\')
        {
            if (!(one_quotes % 2) && !(two_quotes % 2))
                (*word)[i] = str[++start];
            else if (one_quotes % 2 && !(two_quotes % 2))
                (*word)[i] = str[start];
            else if (!(one_quotes % 2) && two_quotes % 2)
            {
                if (str[start + 1] == '$' || str[start + 1] == '\\' || str[start + 1] == '\"')
                    (*word)[i] = str[++start];
                else
                    (*word)[i] = str[start];
            }
        }
        else if(str[start] == '\"')
        {
            two_quotes++;
            if(one_quotes % 2)
            {
                (*word)[i] = str[start];
                two_quotes++;
            }
            else if (!(one_quotes % 2))
                i--;
        }
        else if(str[start] == '\'')
        {
            one_quotes++;
            if(two_quotes % 2 || (str[i - 1] == '\\'))
            {
                (*word)[i] = str[start];
                one_quotes++;
            }
            else if (!(two_quotes % 2))
                i--;
        }
        else 
            (*word)[i] = str[start];
        start++;
        i++;
    }
    return ((*word));
}
