/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_external_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:14:04 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 15:14:14 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->env[++i])
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			return (data->env[i] + 5);
	write(2, "command not found\n", 18);
	ft_free_exit(data, 127);
	return (NULL);
}

char	*ft_get_path_exec(t_data *data, char **dirs, int d_i, int c_i)
{
	char	*path;
	int		len;

	len = ft_strlen(dirs[d_i]) + ft_strlen(data->cmds[c_i]->cmd) + 2;
	path = malloc(sizeof(char) * len);
	if (!path)
	{
		write(2, "malloc error\n", 13);
		ft_env_cleanup(dirs, -1);
		ft_free_exit(data, 1);
	}
	ft_strcpy(path, dirs[d_i]);
	ft_strcat(path, "/");
	ft_strcat(path, data->cmds[c_i]->cmd);
	return (path);
}
