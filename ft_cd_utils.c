#include "minishell.h"

int	ft_handle_pwds(t_data *data)
{
	int	i;
	int	cur_pwd;
	int	old_pwd;

	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
			cur_pwd = i;
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
			old_pwd = i;
	}
	if (!ft_update_oldpwd(data, cur_pwd, old_pwd))
		exit (1);//cleanup needed ?
	if (!ft_update_pwd(data, cur_pwd))
		exit (1);//cleanup needed ??
	return (0);
}

bool	ft_update_oldpwd(t_data *data, int cur_pwd, int old_pwd)
{
	char	*path;
	char	*n_oldpwd;

	path = ft_strchr(data->env[cur_pwd], '/');
	n_oldpwd = ft_strjoin("OLDPWD=", path);
	if (!n_oldpwd)
		return (write (2, "updating oldpwd failed\n", 23), 0);
	free(data->env[old_pwd]);
	data->env[old_pwd] = n_oldpwd;
	return (1);
}

bool	ft_update_pwd(t_data *data, int cur_pwd)
{
	char	*path;
	char	*n_pwd;

	path = getcwd(NULL, 0);
	if (!path)
		return (write (2, "updating pwd failed\n", 20), 0);
	n_pwd = ft_strjoin("PWD=", path);
	if (!n_pwd)
		return (free(path), write (2, "updating pwd failed\n", 20), 0);
	free(path);
	free(data->env[cur_pwd]);
	data->env[cur_pwd] = n_pwd;
	return (1);
}
