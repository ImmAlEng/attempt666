#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (0);
}

int	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (write(1, env[i], ft_strlen(env[i])) == -1)
			return (1);
		if (write(1, "\n", 1) == -1)
			return (1);
	}
	return (0);
}
