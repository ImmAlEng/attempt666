/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:22:26 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:24:08 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_heredoc(t_data *data, int c_i)
{
	int		i;
	t_dlist	*ptr;

	i = 0;
	ptr = data->cmds[c_i]->redirs;
	while (ptr)
	{
		if (((t_redir *)ptr->content)->type == R_HEREDOC)
		{
			i++;
			if (i > 1)
				ft_close(&data->cmds[c_i]->her_pipe[0]);
			ft_redir_her(data, c_i, (((t_redir *)ptr->content)->target),
				(((t_redir *)ptr->content)->quoted));
			if (data->abandon)
				break ;
		}
		ptr = ptr->next;
	}
	return ;
}

static void	ft_set_heredoc_status(t_data *data, int c_i, int status)
{
	if (status == 130)
	{
		data->abandon = true;
		data->cmds[c_i]->exit_status = 130;
		g_exit_status = 130;
		ft_close(&data->cmds[c_i]->her_pipe[0]);
	}
	else if (status != 0)
	{
		data->abandon = true;
		data->cmds[c_i]->exit_status = 1;
		ft_close(&data->cmds[c_i]->her_pipe[0]);
	}
}

void	ft_redir_her(t_data *data, int c_i, char *del, bool quoted)
{
	pid_t	pid;
	int		status;

	if (pipe(data->cmds[c_i]->her_pipe) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
	{
		ft_close(&data->cmds[c_i]->her_pipe[0]);
		ft_close(&data->cmds[c_i]->her_pipe[1]);
		perror("fork");
		data->abandon = true;
		data->cmds[c_i]->exit_status = 1;
		return ;
	}
	if (pid == 0)
		ft_heredoc_child(data, c_i, del, quoted);
	ft_close(&data->cmds[c_i]->her_pipe[1]);
	status = ft_wait_heredoc_child(pid);
	ft_set_heredoc_status(data, c_i, status);
	return ;
}

void	ft_heredoc_loop(t_data *data, int c_i, char *del, bool quoted)
{
	(void)data;
	(void)c_i;
	(void)del;
	(void)quoted;
	return ;
}

void	ft_close_heredoc(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (int)data->n_cmds)
		if (data->cmds[i]->has_heredoc)
			ft_close(&data->cmds[i]->her_pipe[0]);
	return ;
}
