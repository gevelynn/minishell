#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*check;
	void	*f_content;

	res = NULL;
	while (lst)
	{
		if (f)
		{
			f_content = f(lst->content);
			check = ft_lstnew(f_content);
			if (!check)
			{
				del(f_content);
				ft_lstclear(&res, del);
				return (NULL);
			}
			ft_lstadd_back(&res, check);
			lst = lst->next;
		}
	}
	return (res);
}
