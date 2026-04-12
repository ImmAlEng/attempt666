#include "minishell.h"

static int	ft_wait_heredoc_child(pid_t pid)
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

static void	ft_close_inherited_fds(t_data *data, int c_i)
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

static void	ft_heredoc_child(t_data *data, int c_i, char *del, bool quoted)
{
	char	*line;
	struct sigaction	sa_quit;

	ft_reset_signals();
	ft_bzero(&sa_quit, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	ft_close_inherited_fds(data, c_i);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
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
	}
	ft_close(&data->cmds[c_i]->her_pipe[1]);
	ft_close(&data->cmds[c_i]->her_pipe[0]);
	ft_free_data(&data);
	exit(0);
}

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
