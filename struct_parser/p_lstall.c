#include "../minishell.h"

t_data	*p_lstlast(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int		p_lstsize(t_data *lst)
{
	size_t i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	p_lstdelone(t_data *lst, void (*del)(void*))
{
	if (lst)
	{
		if (del)
		{
			del(lst->file_name);
			if ((lst->argv))
			{
				while ((*(lst->argv)))
				{
					del(*(lst->argv));
					lst->argv++;
				}
				del(lst->argv);
			}
		}
		free(lst);
		lst = NULL;
	}
}

void	p_lstclear(t_data **lst, void (*del)(void*))
{
	t_data	*root;
	t_data	*tmp;

	root = *lst;
	while (root)
	{
		tmp = root;
		root = root->next;
		p_lstdelone(tmp, del);
	}
	*lst = NULL;
}

void	p_lstadd_back(t_data **lst, t_data *new)
{
	t_data *tmp;

	if (new && lst)
	{
		tmp = p_lstlast(*lst);
		if (!tmp)
			*lst = new;
		else
			tmp->next = new;
	}
}