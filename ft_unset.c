#include "minishell.h"

int	ft_unset(t_data *data, int cmd_i)
{
	size_t	len;
	int		i;
	int		j;

	i = 0;
	while (data->cmds[cmd_i]->argv[++i])
	{
		j = -1;
		while (data->env[++j])
		{
			len = ft_strlen(data->cmds[cmd_i]->argv[i]);
			if (ft_strncmp(data->cmds[cmd_i]->argv[i], data->env[j], len) == 0
				&& (data->env[j][len] == '=' || data->env[j][len] == '\0'))
			{
				data->env = ft_remove_var(data->env, j);
				if (!data->env)
				{
					data->malloc_err = true;
					exit (1);
				}
				break ;
			}
		}
	}
	return (0);
}

char	**ft_remove_var(char **env, int env_i)
{
	char	**r_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	r_env = malloc(sizeof(char *) * i);
	if (!r_env)
		return (write (2, "env malloc failed\n", 18), NULL);
	i = 0;
	j = 0;
	while (env[j])
	{
		if (j != env_i)
		{
			r_env[i] = env[j];
			i++;
		}
		j++;
	}
	r_env[i] = NULL;
	return (free(env[env_i]), free(env), r_env);
}

bool	ft_env_cleanup(char **env, int env_i)
{
	if (env_i == -1)
	{
		while (env[++env_i])
			free(env[env_i]);
		env_i = 0;
	}
	else if (env_i > 0)
		while (--env_i >= 0)
			free(env[env_i]);
	free(env);
	return (1);
}
