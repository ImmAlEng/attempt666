/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:12:45 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 15:15:52 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wait_external(t_cmd *cmd)
{
	int	status;

	while (waitpid(cmd->pid, &status, 0) == -1)
		if (errno != EINTR)
			break ;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	ft_exec_external(t_data *data)
{
	char	*path;
	t_cmd	*cmd;

	cmd = data->cmds[0];
	cmd->exit_status = 1;
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"), cmd->exit_status);
	if (cmd->pid == 0)
	{
		ft_reset_signals();
		if (!ft_handle_redirs(cmd))
			ft_free_exit(data, 1);
		path = ft_find_binary(data, 0);
		execve(path, cmd->argv, data->env);
		perror("execve");
		if (!ft_strchr(cmd->cmd, '/'))
			free(path);
		ft_free_exit(data, 126 + (errno == ENOENT));
	}
	if (cmd->has_heredoc)
		ft_close(&cmd->her_pipe[0]);
	cmd->exit_status = ft_wait_external(cmd);
	return (cmd->exit_status);
}

static char	*ft_invalid_cmd(t_data *data)
{
	write(2, "command not found\n", 18);
	ft_free_exit(data, 127);
	return (NULL);
}

static char	*ft_find_in_path(t_data *data, int c_i, char **dirs)
{
	int		i;
	char	*path;

	i = -1;
	while (dirs[++i])
	{
		path = ft_get_path_exec(data, dirs, i, c_i);
		if (access(path, X_OK) == 0)
			return (ft_env_cleanup(dirs, -1), path);
		free(path);
	}
	ft_env_cleanup(dirs, -1);
	return (ft_invalid_cmd(data));
}

char	*ft_find_binary(t_data *data, int c_i)
{
	char	*path_env;
	char	**dirs;

	if (!data || !data->cmds || !data->cmds[c_i] || !data->cmds[c_i]->cmd
		|| !*data->cmds[c_i]->cmd)
		return (ft_invalid_cmd(data));
	if (ft_strchr(data->cmds[c_i]->cmd, '/'))
		return (data->cmds[c_i]->cmd);
	path_env = ft_get_path_env(data);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (write(2, "malloc error\n", 13),
			ft_free_exit(data, 1), NULL);
	return (ft_find_in_path(data, c_i, dirs));
}
