#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

int         check_dollar(t_all *all, char **word, int start, int *arr)
{
    int     len;
    char    *tmp;
    char    *tempory = NULL; //временная
    int     question_mark;

    question_mark = 0;
    tmp = ft_strdup((*word)); //сохранили слово
    if (((*word)[start]) == '?')
    {
        question_mark = 1;
        tempory = ft_itoa(all->exit_status);
    }
    else if (!(tempory = get_env_str(((*word) + start), all)))
        tempory = ft_strdup(""); //почистить
    len = ft_strlen(tempory);
    free(*word);
    (*word) = ft_calloc(arr[1] - arr[0] + len + 1, sizeof(char)); // выделили новую память с учетом переменной окружения
    len = -1;
    while(++len < start)
        (*word)[len] = tmp[len]; // копируем строку обратно в (*word) до знака $
        // после того как дошли до доллара, то вместо названия переменной окружения добавали путь
    ft_strlcat((*word), tempory, ft_strlen(tempory) + ft_strlen(*word) + 1);
    if (tempory[0] == '\0' || question_mark == 1)
        free(tempory);
    len = ft_strlen((*word));
    free(tmp);
    return (len);
}

void        search_dollar(char **word, char *str, int **start, int *i)
{
    int num;
    int check;

    num = (*start)[0];
    check = *i; //запомнили место куда будет переписана переменная окружения в word
    (*start)[0]++;
    while (str[(*start)[0]] && str[(*start)[0]] != '\'' && str[(*start)[0]] != '\"' && str[(*start)[0]] != ' ' &&
        str[(*start)[0]] != '$' && str[(*start)[0]] != '\\')
    {
        if (str[num] == '$' && ((ft_isdigit(str[num + 1]) && ft_isdigit(str[num + 2])) || str[num + 1] == '?'))
        {
            (*word)[*i] = str[(*start)[0]];
            (*word)[(*i)++] = str[(*start)[0]++];
            break ;
        }
        (*word)[(*i)] = str[(*start)[0]];
        (*start)[0]++;
        (*i)++;
    }
    *i = check;
}

// (*start)[0] и (*start)[1] начало и конец аргумента по строке str
char        *search_variable(t_all *all, char **word, char *str, int **start)
{
    int     i;
    int     quotes[2];
    int     arr[2];

    i = 0;
    quotes[0] = 0;
    quotes[1] = 0;
    arr[0] = (*start)[0];
    arr[1] = (*start)[1];

    while ((*start)[0] < (*start)[1])
    {
        //------------------------------------------------------------
        if (str[(*start)[0]] == '$' && !(quotes[0] % 2) && (ft_isalnum(str[(*start)[0] + 1]) ||
            str[(*start)[0] + 1] == '_' || str[(*start)[0] + 1] == '?'))
        {
            search_dollar(word, str, start, &i);
            i = check_dollar(all, word, i, arr); //возвращает длину строки word  с подставленной переменной окружения
            (*start)[0]--;
            i--;
        }
        //------------------------------------------------------------
        else if (str[(*start)[0]] == '\\')
        {
            if (!(quotes[0] % 2) && !(quotes[1] % 2))
                (*word)[i] = str[++(*start)[0]];
            else if (quotes[0] % 2 && !(quotes[1] % 2))
                (*word)[i] = str[(*start)[0]];
            else if (!(quotes[0] % 2) && quotes[1] % 2)
            {
                if (str[(*start)[0] + 1] == '$' || str[(*start)[0] + 1] == '\\' || str[(*start)[0] + 1] == '\"')
                    (*word)[i] = str[++(*start)[0]];
                else
                    (*word)[i] = str[(*start)[0]];
            }
        }
        else if(str[(*start)[0]] == '\"')
        {
            quotes[1]++;
            if(quotes[0] % 2)
            {
                (*word)[i] = str[(*start)[0]];
                quotes[1]++;
            }
            else if (!(quotes[0] % 2))
                i--;
        }
        else if(str[(*start)[0]] == '\'')
        {
            quotes[0]++;
            if(quotes[1] % 2 || (str[i - 1] == '\\'))
            {
                (*word)[i] = str[(*start)[0]];
                quotes[0]++;
            }
            else if (!(quotes[1] % 2))
                i--;
        }
        else 
            (*word)[i] = str[(*start)[0]];
        (*start)[0]++;
        i++;
    }
    return ((*word));
}
