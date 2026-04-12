/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:45:14 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:45:19 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_add_var(t_data *data, char *argv)
{
	data->env = ft_actual_export(data, argv);
	if (!data->env)
	{
		write(2, "env malloc failed\n", 18);
		data->malloc_err = true;
		exit(1);
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

static char	*ft_cmd_last_arg(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (NULL);
	i = 0;
	while (cmd->argv[i + 1])
		i++;
	return (cmd->argv[i]);
}

static bool	ft_set_env_value(t_data *data, char *name, char *value)
{
	char	*entry;
	int		env_i;

	entry = ft_strjoin(name, value);
	if (!entry)
		return (data->malloc_err = true, false);
	env_i = ft_var_present(data, entry);
	if (env_i != -1)
		ft_modify_var(data, entry, env_i);
	else
		ft_add_var(data, entry);
	return (free(entry), true);
}

bool	ft_update_underscore(t_data *data, t_cmd *cmd)
{
	char	*last;

	last = ft_cmd_last_arg(cmd);
	if (!data || !last)
		return (true);
	return (ft_set_env_value(data, "_=", last));
}
