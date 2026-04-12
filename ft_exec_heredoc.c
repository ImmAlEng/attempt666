/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:24:12 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:24:13 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait_heredoc_child(pid_t pid)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
		if (errno != EINTR)
			return (1);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	ft_close_inherited_fds(t_data *data, int c_i)
{
	int	i;

	i = -1;
	while (++i < (int)data->n_cmds - 1)
	{
		ft_close_if(&data->cmds[i]->pipe[0]);
		ft_close_if(&data->cmds[i]->pipe[1]);
	}
	i = -1;
	while (++i < (int)data->n_cmds)
	{
		ft_close_if(&data->cmds[i]->her_pipe[0]);
		if (i != c_i)
			ft_close_if(&data->cmds[i]->her_pipe[1]);
	}
}

bool	ft_heredoc_process_line(t_data *data, int c_i,
		char *del, bool quoted)
{
	char	*line;

	line = readline("> ");
	if (!line)
		return (false);
	if (ft_strcmp(line, del) == 0)
		return (free(line), false);
	if (!quoted)
	{
		line = ft_heredoc_expand(data, line);
		if (!line)
		{
			ft_free_data(&data);
			exit(1);
		}
	}
	write(data->cmds[c_i]->her_pipe[1], line, ft_strlen(line));
	write(data->cmds[c_i]->her_pipe[1], "\n", 1);
	free(line);
	return (true);
}

void	ft_heredoc_child(t_data *data, int c_i, char *del, bool quoted)
{
	struct sigaction	sa_quit;

	ft_reset_signals();
	ft_bzero(&sa_quit, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	ft_close_inherited_fds(data, c_i);
	while (ft_heredoc_process_line(data, c_i, del, quoted))
		;
	ft_close(&data->cmds[c_i]->her_pipe[1]);
	ft_close(&data->cmds[c_i]->her_pipe[0]);
	ft_free_data(&data);
	exit(0);
}
