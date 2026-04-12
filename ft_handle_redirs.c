#include "minishell.h"

static bool	ft_handle_heredoc_redir(t_cmd *cmd, int *i)
{
	(*i)++;
	if (*i == cmd->n_heredoc)
	{
		if (dup2(cmd->her_pipe[0], STDIN_FILENO) == -1)
			return (ft_close(&cmd->her_pipe[0]), 0);
	}
	return (1);
}

bool	ft_handle_redirs(t_cmd *cmd)
{
	int		i;
	t_dlist	*ptr;

	i = 0;
	ptr = cmd->redirs;
	while (ptr)
	{
		if (((t_redir *)ptr->content)->type == R_IN)
			if (!ft_redir_in(cmd, ((t_redir *)ptr->content)->target))
				return (0);
		if (((t_redir *)ptr->content)->type == R_OUT)
			if (!ft_redir_out(cmd, ((t_redir *)ptr->content)->target))
				return (0);
		if (((t_redir *)ptr->content)->type == R_APPEND)
			if (!ft_redir_app(cmd, ((t_redir *)ptr->content)->target))
				return (0);
		if (((t_redir *)ptr->content)->type == R_HEREDOC)
			if (!ft_handle_heredoc_redir(cmd, &i))
				return (0);
		ptr = ptr->next;
	}
	return (1);
}

bool	ft_redir_in(t_cmd *cmd, char *target)
{
	cmd->fd_in = open(target, O_RDONLY);
	if (cmd->fd_in == -1)
		return (perror("open"), 0);
	if (dup2(cmd->fd_in, STDIN_FILENO))
		return (perror("dup2"), ft_close(&cmd->fd_in), 0);
	ft_close(&cmd->fd_in);
	return (1);
}

bool	ft_redir_out(t_cmd *cmd, char *target)
{
	cmd->fd_out = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
		return (perror("open"), 0);
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (perror("dup2"), ft_close(&cmd->fd_out), 0);
	ft_close(&cmd->fd_out);
	return (1);
}

bool	ft_redir_app(t_cmd *cmd, char *target)
{
	cmd->fd_out = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->fd_out == -1)
		return (perror("open"), 0);
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (perror("dup2"), ft_close(&cmd->fd_out), 0);
	ft_close(&cmd->fd_out);
	return (1);
}
