#include "minishell.h"

int	ft_cd(t_data *data, int cmd_i)
{
	if (data->cmds[cmd_i]->argv[2])
		return (write (2, "too many args\n", 14), 1);
	if (!data->cmds[cmd_i]->argv[1])
		return (ft_cd_home(data));
	return (ft_cd_with_arg(data, cmd_i));
}

int	ft_cd_home(t_data *data)
{
	char	*home;

	home = ft_home_path(data);
	if (!home)
		exit (1);
	if (chdir(home) == -1)
		return (perror("cd"), 1);
	return (ft_handle_pwds(data));
}

int	ft_cd_with_arg(t_data *data, int cmd_i)
{
	if (chdir(data->cmds[cmd_i]->argv[1]) == -1)
		return (perror("cd"), 1);
	return (ft_handle_pwds(data));
}

char	*ft_home_path(t_data *data)
{
	int	i;

	i = -1;
	while (data->env[++i])
		if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
			return (ft_strchr(data->env[i], '/'));
	write (2, "$HOME path not found\n", 21);
	return (NULL);
}
