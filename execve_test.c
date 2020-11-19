#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

void	exec_cmds(t_all *all, char **argv)
{
	int		pid;
	int		status;
	int		execve_ret;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		execve_ret = 0;
		if ((ft_strncmp("./", argv[0], 2)) == 0 ||
			(ft_strncmp("../", argv[0], 3)) == 0 || (ft_strncmp("/", argv[0], 1)) == 0)
			execve_ret = execve(argv[0], argv, all->env_vars);
		else if ((path = find_file_in_path(argv[0], all)))
		{
			execve_ret = execve(path, argv, all->env_vars);
			free(path);
		}
		else
		{
			ft_putstr_fd("msh: command not found: ", 2);
			ft_putendl_fd(argv[0], 2);
		}
		if (execve_ret == -1)
			perror(argv[0]);
		exit(execve_ret);
	}
	else
		wait(&status);
}

char	*find_file_in_path(char	*file_name, t_all *all)
{
	char	*path_slashed;
	char	**splited_path;
	char	*absolute_filename;
	int		env_line;
	int		i;
	struct stat buf;
	int		stat_ret;

	i = 0;
	if ((env_line = get_env_line("PATH=", all)) == -1)
		return (NULL);
	splited_path = ft_split(all->env_vars[env_line] + 5, ':');
	while (splited_path[i])
	{
		path_slashed = ft_strjoin(splited_path[i], "/");
		absolute_filename = ft_strjoin(path_slashed, file_name);
		free(path_slashed);
		stat_ret = stat(absolute_filename, &buf); 
		if (stat_ret == 0)
			return (absolute_filename);
		free(absolute_filename);
		i++;
	}
	free_ptrs_array(splited_path);
	return (NULL);
}




























