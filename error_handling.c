#include "minishell.h"

void	error_message(char *text_error)
{
	ft_putstr_fd(text_error, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}