#include "minishell.h"

void	print_error_with_arg(char *command, char *argument,
	char *error_message)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	if (error_message)
		ft_putstr_fd(": ", 2);
	else
		ft_putstr_fd(" ", 2);
	ft_putstr_fd("`", 2);
	if (argument && *argument)
		ft_putstr_fd(argument, 2);
	ft_putstr_fd("\'", 2);
	if (error_message)
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(error_message, 2);
	}
	else
		ft_putstr_fd("\n", 2);
}

int		print_error(char *command, char *argument, char *error_message)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	if (argument && *argument)
	{
		ft_putstr_fd(argument, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error_message, 2);
	return (-1);
}

void	print_error_and_exit(char *command, char *argument,
	char *error_message, int exit_status)
{
	print_error(command, argument, error_message);
	if (exit_status != -1)
		exit(exit_status);
}
