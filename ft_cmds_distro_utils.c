/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_distro_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:08:48 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:09:20 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmds_check(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (int)data->n_cmds)
	{
		ft_has_heredoc(data->cmds[i]);
		if (ft_is_builtin(data->cmds[i]))
		{
			data->cmds[i]->is_builtin = true;
			if (data->n_cmds > 1)
				data->cmds[i]->needs_fork = true;
			else
				data->cmds[i]->needs_fork = false;
		}
		else
		{
			data->cmds[i]->is_builtin = false;
			data->cmds[i]->needs_fork = true;
		}
	}
	return ;
}

void	ft_has_heredoc(t_cmd *cmd)
{
	t_dlist	*ptr;

	cmd->n_heredoc = 0;
	ptr = cmd->redirs;
	while (ptr)
	{
		if (((t_redir *)ptr->content)->type == R_HEREDOC)
			cmd->n_heredoc++;
		ptr = ptr->next;
	}
	if (cmd->n_heredoc > 0)
		cmd->has_heredoc = true;
	else
		cmd->has_heredoc = false;
	return ;
}

bool	ft_is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd)
		return (0);
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (1);
	return (0);
}
