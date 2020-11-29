#include "../libft/libft.h"
#include "../minishell.h"


void	error_malloc()
{
		write(1, "Error malloc\n", 13);
		return ;
}

void filling_struct(t_all *all, t_list *new, int len)
{
	int		i;
	t_data	*temp;

	i = 0;
	temp = all->data;
	while (temp->next)
		temp = temp->next;
	temp->args = ft_calloc(len + 1, sizeof(char *));
	while(new)
	{
		temp->args[i] = new->content;
		new = new->next;
		i++;
	}
}
