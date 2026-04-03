#include "minishell.h"

bool	ft_create_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (int)data->n_cmds - 1)
	{
		if (pipe(data->cmds[i]->pipe) == -1)
		{
			perror("pipe");
			data->cmds[i]->exit_status = 1;
			while (--i >= 0)
			{
				close(data->cmds[i]->pipe[0]);
				close(data->cmds[i]->pipe[1]);
			}
			return (0);
		}
	}
	return (1);
}

void	ft_close_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (int)data->n_cmds - 1)
	{
		close(data->cmds[i]->pipe[0]);
		close(data->cmds[i]->pipe[1]);
	}
	return ;
}

void	ft_handle_pipes(t_data *data, int i)
{
	if (i != 0)
	{//first cmd no stdin dup
		if (dup2(data->cmds[i - 1]->pipe[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit (1);
		}
	}
	if (i != (int)data->n_cmds - 1)
	{//last cmd no stdout dup
		if (dup2(data->cmds[i]->pipe[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit (1);
		}
	}
	ft_close_pipes(data);
	return ;
}
