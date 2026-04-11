#include "minishell.h"

int	ft_exec_builtin(t_data *data, int i)
{
	int	std_out;
	int	std_in;
	bool	has_redir;//maybe into cmd struct

	data->cmds[i]->exit_status = 1;
	has_redir = (data->cmds[i]->redirs != NULL);
	if (!has_redir)
		return (ft_run_builtin(data, i));
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	if (std_in == -1 || std_out == -1)
	{
		perror("dup");
		ft_free_exit(data, 1, i);
	}
	if (ft_handle_redirs(data->cmds[i]))
		data->cmds[i]->exit_status = ft_run_builtin(data, i);
	if (dup2(std_out, STDOUT_FILENO) == -1 || dup2(std_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		ft_free_exit(data, 1, i);
	}
	if (data->cmds[i]->has_heredoc)
		close(data->cmds[i]->her_pipe[0]);
	close(std_out);
	close(std_in);
	return (data->cmds[i]->exit_status);
}

int	ft_run_builtin(t_data *data, int i)
{
	if (ft_strcmp(data->cmds[i]->cmd, "echo") == 0)
		return (ft_echo(data->cmds[i]));
	if (ft_strcmp(data->cmds[i]->cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(data->cmds[i]->cmd, "env") == 0)
		return (ft_env(data, i));
	if (ft_strcmp(data->cmds[i]->cmd, "unset") == 0)
		return (ft_unset(data, i));
	if (ft_strcmp(data->cmds[i]->cmd, "export") == 0)
		return (ft_export(data, i));
	if (ft_strcmp(data->cmds[i]->cmd, "cd") == 0)
		return (ft_cd(data, i));
	if (ft_strcmp(data->cmds[i]->cmd, "exit") == 0)
		return (ft_exit(data, i));
	return (1);
}
