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
			exit(1);
		path = ft_find_binary(data, 0);
		execve(path, cmd->argv, data->env);
		perror("execve");
		ft_free_exit(data, 126 + (errno == ENOENT));
	}
	if (cmd->has_heredoc)
		close(cmd->her_pipe[0]);
	cmd->exit_status = ft_wait_external(cmd);
	return (cmd->exit_status);
}

char	*ft_find_binary(t_data *data, int c_i)
{
	int		i;
	char	*path_env;
	char	*path;
	char	**dirs;

	if (!data || !data->cmds || !data->cmds[c_i] || !data->cmds[c_i]->cmd
		|| !*data->cmds[c_i]->cmd)
		return (write(2, "command not found\n", 18), exit(127), NULL);
	if (ft_strchr(data->cmds[c_i]->cmd, '/'))
		return (data->cmds[c_i]->cmd);
	path_env = ft_get_path_env(data);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (write(2, "malloc error\n", 13), exit(1), NULL);
	i = -1;
	while (dirs[++i])
	{
		path = ft_get_path_exec(data, dirs, data->cmds[c_i]->cmd, i);
		if (access(path, X_OK) == 0)
			return (ft_env_cleanup(dirs, -1), path);
		free(path);
	}
	ft_env_cleanup(dirs, -1);
	write(2, "command not found\n", 18);
	return (ft_free_exit(data, 127), NULL);
}

char	*ft_get_path_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->env[++i])
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
			return (data->env[i] + 5);
	write(2, "command not found\n", 18);
	ft_free_exit(data, 127);
	return (NULL);
}

char	*ft_get_path_exec(t_data *data, char **dirs, char *cmd, int i)
{
	char	*path;
	int		len;

	len = ft_strlen(dirs[i]) + ft_strlen(cmd) + 2;
	path = malloc(sizeof(char) * len);
	if (!path)
	{
		write(2, "malloc error\n", 13);
		if (ft_env_cleanup(dirs, -1))
			ft_free_exit(data, 1);
	}
	ft_strcpy(path, dirs[i]);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	return (path);
}
