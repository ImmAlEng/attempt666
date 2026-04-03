#include "minishell.h"

int	ft_exec_external(t_data *data)
{
	char	*path;
	int		status;

	data->cmds[0]->exit_status = 1;//check ft_exec_builtin not sure if neccessary tho
	data->cmds[0]->pid = fork();
	if (data->cmds[0]->pid == -1)
		return (perror("fork"), data->cmds[0]->exit_status);
	if (data->cmds[0]->pid == 0)
	{
		ft_reset_signals();
		if (!ft_handle_redirs(data->cmds[0]))
			exit (1);
		path = ft_find_binary(data, 0);
		execve(path, data->cmds[0]->argv, data->env);
		perror("execve");
		exit (1);
	}
	if (data->cmds[0]->has_heredoc)
		close(data->cmds[0]->her_pipe[0]);
	waitpid(data->cmds[0]->pid, &status, 0);
	if (WIFEXITED(status))
		data->cmds[0]->exit_status = WEXITSTATUS(status);
	return (data->cmds[0]->exit_status);
}

char	*ft_find_binary(t_data *data, int c_i)
{
	int		i;
	char	*path_env;
	char	*path;
	char	**dirs;

	if (ft_strchr(data->cmds[c_i]->cmd, '/'))
		return (data->cmds[c_i]->cmd);
	path_env = ft_get_path_env(data->env);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		if (write (2, "malloc error\n", 13) != -1)
			exit (1);
	i = -1;
	while (dirs[++i])
	{
		path = ft_get_path_exec(dirs, data->cmds[c_i]->cmd, i);
		if (access(path, X_OK) == 0)
			return (ft_env_cleanup(dirs, -1), path);
		free(path);
	}
	ft_env_cleanup(dirs, -1);
	write(2, "command not found\n", 18);//this also happens in case of "echoo" or "cdd" kennts besser lösen but it works blyat
	exit (127);
}

char	*ft_get_path_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
	write (2, "$PATH variable doesn't exist\n", 29);
	exit (1);
}

char	*ft_get_path_exec(char **dirs, char *cmd, int i)
{
	char	*path;
	int		len;

	len = ft_strlen(dirs[i]) + ft_strlen(cmd) + 2;
	path = malloc(sizeof(char) * len);
	if (!path)
	{
		write (2, "malloc error\n", 13);
		if (ft_env_cleanup(dirs, -1))
			exit (1);
	}
	ft_strcpy(path, dirs[i]);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	return (path);
}
