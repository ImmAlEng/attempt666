/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:28:01 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:34:24 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_pipeline(t_data *data)
{
	int		i;
	int		j;
	int		status;
	char	*path;

	j = -1;
	while (++j < (int)data->n_cmds)
		data->cmds[j]->exit_status = 1;
	i = -1;
	path = NULL;
	if (ft_create_pipes(data))
	{
		if (!ft_run_pipeline(data, i, &status, path))
		{
			ft_update_underscore(data, data->cmds[data->n_cmds - 1]);
			return (data->cmds[data->n_cmds - 1]->exit_status);
		}
	}
	return (1);
}
