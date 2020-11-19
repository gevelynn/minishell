#include "minishell.h"

void	free_ptrs_array(char **ptr_array)
{
	size_t i;

	i = 0;
	if (ptr_array)
	{
		while (ptr_array[i])
		{
			free(ptr_array[i]);
			ptr_array[i] = NULL;
			i++;
		}
		free(ptr_array);
	}
}

void	envp_saving(char **envp, t_all *all)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (envp[i])
		i++;
	all->env_amount = i;
	if (!(all->env_vars = (char **)malloc(sizeof(char *) * (i + 1))))
		return ;
	i = 0;
	while (envp[i])
	{
		len = ft_strlen(envp[i]);
		if (!(all->env_vars[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (free_ptrs_array(all->env_vars));
		ft_strlcpy(all->env_vars[i], envp[i], len + 1);
		i++;
	}
	all->env_vars[i] = NULL;
}

void	parser(t_all *all)
{
	char *line;
	char **splited;
	
	while (get_next_line(0, &line) > 0)
	{
		if ((splited = ft_split(line, ' ')))
		{
			if (ft_strncmp("cd", splited[0], 3) == 0)
				ft_cd(splited[1], all);
			else if (ft_strncmp("pwd", splited[0], 4) == 0)
				ft_pwd();
			else if (ft_strncmp("env", splited[0], 4) == 0)
				ft_env(all);
			else if (ft_strncmp("unset", splited[0], 6) == 0)
				ft_unset(all, &(splited[1]));
			else if (ft_strncmp("export", splited[0], 7) == 0)
				ft_export(all, &(splited[1]));
			else if (ft_strncmp("q", splited[0], 2) == 0)
				break;
			else
				exec_cmds(all, splited);
		}
		free(line);
		line = NULL;
		free_ptrs_array(splited);
		ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_all all;

	if (argc != 1 || !argv)
	{
		ft_putendl_fd("No parameters needed", 2);
		return (-1);
	}
	envp_saving(envp, &all);
	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	parser(&all);
	return (0);
}
