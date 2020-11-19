#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (new && lst)
	{
		tmp = ft_lstlast(*lst);
		if (!tmp)
			*lst = new;
		else
			tmp->next = new;
	}
}
