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
		close(cmd->her_pipe[0]);
	close(std_out);
	close(std_in);
	return (exit_status);
}

int	ft_cmds_distro(t_data *data)
{
	ft_cmds_check(data);
	if (data->n_cmds > 1)
		return (ft_exec_pipeline(data));
	else
	{
		if (data->cmds[0]->has_heredoc)
			ft_exec_heredoc(data, 0);
		if (!data->cmds[0]->cmd)
			return (ft_exec_redirs_only(data->cmds[0]));
		if (data->cmds[0]->is_builtin)
			return (ft_exec_builtin(data, 0));
		else
			return (ft_exec_external(data));
	}
	return (1);
}

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
