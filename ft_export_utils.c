#include "minishell.h"

bool	ft_export_valid(char *argv)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argv[i]) && argv[i] != '_')
		return (0);
	while (argv[++i])
	{
		if (!ft_isalnum(argv[i]) && argv[i] != '_' && argv[i] != '=')
			return (0);
		if (argv[i] == '=')
			break ;
	}
	return (1);
}

int	ft_var_present(t_data *data, char *argv)
{
	int	i;
	int	j;

	i = -1;
	while (data->env[++i])
	{
		j = 0;
		while (data->env[i][j] == argv[j])
		{
			if ((data->env[i][j + 1] == '=' || data->env[i][j + 1] == '\0')
					&& argv[j + 1] == '=')
				return (i);
			j++;
		}
	}
	return (-1);
}

bool	ft_modify_var(t_data *data, char *argv, int env_i)
{
	free(data->env[env_i]);
	data->env[env_i] = ft_strdup(argv);
	if (!data->env[env_i])
	{
		write (2, "env malloc failed\n", 18);
		data->malloc_err = true;
		exit (1);//??
	}
	return (1);
}

bool	ft_add_var(t_data *data, char *argv)
{
	data->env = ft_actual_export(data, argv);
	if (!data->env)
	{
		write (2, "env malloc failed\n", 18);
		data->malloc_err = true;
		exit (1);//??
	}
	return (1);
}

char	**ft_actual_export(t_data *data, char *argv)
{
	char	**r_env;
	int		i;

	i = 0;
	while (data->env[i])
		i++;
	r_env = malloc(sizeof(char *) * (i + 2));
	if (!r_env)
		return (NULL);
	i = -1;
	while (data->env[++i])
		r_env[i] = data->env[i];
	r_env[i] = ft_strdup(argv);
	if (!r_env[i])
		return (ft_env_cleanup(r_env, i), NULL);
	r_env[i + 1] = NULL;
	return (free(data->env), r_env);
}
