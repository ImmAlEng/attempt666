/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_distro.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:07:27 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:08:05 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_redirs_only(t_cmd *cmd)
{
	int	std_out;
	int	std_in;
	int	exit_status;

	exit_status = 1;
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	if (std_in == -1 || std_out == -1)
		return (perror("dup"), 1);
	if (ft_handle_redirs(cmd))
		exit_status = 0;
	if (dup2(std_out, STDOUT_FILENO) == -1 || dup2(std_in, STDIN_FILENO) == -1)
		return (perror("dup2"), close(std_out), close(std_in), 1);
	if (cmd->has_heredoc)
		ft_close(&cmd->her_pipe[0]);
	close(std_out);
	close(std_in);
	return (exit_status);
}

static int	ft_exec_one_cmd(t_data *data)
{
	int	status;

	if (data->cmds[0]->has_heredoc)
		ft_exec_heredoc(data, 0);
	if (data->abandon)
		return (data->cmds[0]->exit_status);
	if (!data->cmds[0]->cmd)
		return (ft_exec_redirs_only(data->cmds[0]));
	if (data->cmds[0]->is_builtin)
		status = ft_exec_builtin(data, 0);
	else
		status = ft_exec_external(data);
	ft_update_underscore(data, data->cmds[0]);
	return (status);
}

int	ft_cmds_distro(t_data *data)
{
	ft_cmds_check(data);
	if (data->n_cmds > 1)
		return (ft_exec_pipeline(data));
	return (ft_exec_one_cmd(data));
}
