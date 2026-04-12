/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:41:38 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:41:39 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_data *data, int cmd_i)
{
	int	i;
	int	env_i;

	if (!data->cmds[cmd_i]->argv[1])
		return (ft_print_export_var(data->env));
	else
	{
		i = 0;
		while (data->cmds[cmd_i]->argv[++i])
		{
			if (ft_export_valid(data->cmds[cmd_i]->argv[i]))
			{
				env_i = ft_var_present(data, data->cmds[cmd_i]->argv[i]);
				if (env_i != -1)
					ft_modify_var(data, data->cmds[cmd_i]->argv[i], env_i);
				else
					ft_add_var(data, data->cmds[cmd_i]->argv[i]);
			}
			else
				return (write(2, "arg not valid\n", 14), 1);
		}
		return (0);
	}
}

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
		write(2, "env malloc failed\n", 18);
		data->malloc_err = true;
		exit(1);
	}
	return (1);
}
