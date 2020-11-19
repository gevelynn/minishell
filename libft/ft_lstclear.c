#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*root;
	t_list	*tmp;

	root = *lst;
	while (root)
	{
		tmp = root;
		root = root->next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
