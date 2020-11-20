#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "./libft/libft.h"

typedef	struct s_all
{
	char	**env_vars;
	size_t	env_amount;
}				t_all;

typedef struct		s_data
{
	char			**argv;
	char			*file_name;
	int				pipe;
	int				red_to;
	int				doub_red_to;
	int				red_from;
	struct s_data	*next;
}					t_data;

/*
**		parser
*/
t_data	*p_lstnew(void);
void	p_lstadd_back(t_data **lst, t_data *new);
void	p_lstclear(t_data **lst, void (*del)(void*));
t_data	*p_lstlast(t_data *lst);
int		p_lstsize(t_data *lst);
/*
**		builtins
*/
int		ft_cd(char *path, t_all *all);
int		ft_pwd(void);
void	ft_env(t_all *all);
void	ft_unset(t_all *all, char **args);
void	ft_export(t_all *all, char **args);
/*
**		utils
*/
void	free_ptrs_array(char **ptr_array);
void	exec_cmds(t_all *all, char **argv);
void	stat_test(char **file_names);
int		get_env_line(char *to_find, t_all *all);
char	*find_file_in_path(char	*file_name, t_all *all);

#endif
