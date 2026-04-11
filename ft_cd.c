#include "minishell.h"

static int	ft_cd_oldpwd(t_data *data)
{
	int		i;
	char	*oldpwd;

	i = -1;
	while (data->env[++i])
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
			break ;
	if (!data->env[i])
		return (write(2, "cd: OLDPWD not set\n", 19), 1);
	oldpwd = data->env[i] + 7;
	if (chdir(oldpwd) == -1)
		return (perror("cd"), 1);
	write(1, oldpwd, ft_strlen(oldpwd));
	write(1, "\n", 1);
	return (ft_handle_pwds(data));
}

int	ft_cd(t_data *data, int cmd_i)
{
	if (data->cmds[cmd_i]->argv[1] && data->cmds[cmd_i]->argv[2])
		return (write(2, "too many args\n", 14), 2);
	if (data->cmds[cmd_i]->argv[1]
		&& ft_strcmp(data->cmds[cmd_i]->argv[1], "-") == 0)
		return (ft_cd_oldpwd(data));
	if (!data->cmds[cmd_i]->argv[1])
		return (ft_cd_home(data));
	return (ft_cd_with_arg(data, cmd_i));
}

int	ft_cd_home(t_data *data)
{
	char	*home;

	home = ft_home_path(data);
	if (!home)
		return (1);
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
	write(2, "$HOME path not found\n", 21);
	return (NULL);
}
