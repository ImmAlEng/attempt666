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
			if (i > 1)		//last one get closed in ft_handle_redirs
				close(data->cmds[c_i]->her_pipe[0]);
			ft_redir_her(data, c_i, (((t_redir *)ptr->content)->target),
				(((t_redir *)ptr->content)->quoted));
		}
		ptr = ptr->next;
	}
	return ;
}

void	ft_redir_her(t_data *data, int c_i, char *del, bool quoted)
{
	if (pipe(data->cmds[c_i]->her_pipe) == -1)
		return (perror("pipe"));
	ft_heredoc_loop(data, c_i, del, quoted);
	return ;
}

void	ft_heredoc_loop(t_data *data, int c_i, char *del, bool quoted)
{
	//jemand hat gmeint i sollt lieber alles in a file speichern und dann erst writen
	char	*line;

	while (1)
	{
		line = readline ("> ");
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
				return ;
		}
		write (data->cmds[c_i]->her_pipe[1], line, ft_strlen(line));
		write (data->cmds[c_i]->her_pipe[1], "\n", 1);
		free(line);
	}
	close(data->cmds[c_i]->her_pipe[1]);
	return ;
}

void	ft_close_heredoc(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (int)data->n_cmds)
		if (data->cmds[i]->has_heredoc)
			close(data->cmds[i]->her_pipe[0]);
	return ;
}
