#include "minishell.h"

int	ft_exec_builtin(t_data *data, int i)
{
	int	std_out;
	int	std_in;

	data->cmds[i]->exit_status = 1;
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	if (std_in == -1 || std_out == -1)
	{
		perror("dup");
		exit(1);
	}
	if (ft_handle_redirs(data->cmds[i]))
		data->cmds[i]->exit_status = ft_run_builtin(data, i);
	if (dup2(std_out, STDOUT_FILENO) == -1 || dup2(std_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (data->cmds[i]->has_heredoc)
		close(data->cmds[i]->her_pipe[0]);
	close(std_out);
	close(std_in);
	return (data->cmds[i]->exit_status);
}

int	ft_run_builtin(t_data *data, int i)
{
	if (ft_strncmp(data->cmds[i]->cmd, "echo", 4) == 0)
		return (ft_echo(data->cmds[i]));
	if (ft_strncmp(data->cmds[i]->cmd, "pwd", 3) == 0)
		return (ft_pwd());
	if (ft_strncmp(data->cmds[i]->cmd, "env", 3) == 0)
		return (ft_env(data->env));
	if (ft_strncmp(data->cmds[i]->cmd, "unset", 5) == 0)
		return (ft_unset(data, i));
	if (ft_strncmp(data->cmds[i]->cmd, "export", 6) == 0)
		return (ft_export(data, i));
	if (ft_strncmp(data->cmds[i]->cmd, "cd", 2) == 0)
		return (ft_cd(data, i));
	if (ft_strcmp(data->cmds[i]->cmd, "exit") == 0)
		return (ft_exit(data, i));
	return (1);
}
