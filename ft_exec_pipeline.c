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

static void	ft_exec_child(t_data *data, int i, char *path)
{
	ft_reset_signals();
	ft_handle_pipes(data, i);
	if (data->cmds[i]->is_builtin)
		exit(ft_exec_builtin(data, i));
	if (!ft_handle_redirs(data->cmds[i]))
		exit(1);
	if (!data->cmds[i]->cmd)
		exit(0);
	path = ft_find_binary(data, i);
	execve(path, data->cmds[i]->argv, data->env);
	perror("execve");
	exit(1);
}

int	ft_run_pipeline(t_data *data, int i, int *status, char *path)
{
	while (++i < (int)data->n_cmds)
	{
		if (data->cmds[i]->has_heredoc)
			ft_exec_heredoc(data, i);
		data->cmds[i]->pid = fork();
		if (data->cmds[i]->pid == -1)
			return (perror("fork"), data->cmds[i]->exit_status);
		if (data->cmds[i]->pid == 0)
			ft_exec_child(data, i, path);
	}
	ft_close_heredoc(data);
	ft_close_pipes(data);
	ft_wait_kiddo(data, status);
	return (data->cmds[data->n_cmds - 1]->exit_status);
}

void	ft_wait_kiddo(t_data *data, int *status)
{
	int	i;

	i = -1;
	while (++i < (int)data->n_cmds)
	{
		while (waitpid(data->cmds[i]->pid, status, 0) == -1)
			if (errno != EINTR)
				break ;
		if (WIFEXITED(*status))
			data->cmds[i]->exit_status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			data->cmds[i]->exit_status = 128 + WTERMSIG(*status);
	}
	return ;
}
