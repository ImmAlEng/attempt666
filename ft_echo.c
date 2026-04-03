#include "minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	l;

	i = 1;
	l = 1;
	while (cmd->argv[i] && ft_n_flag(cmd->argv[i]))
	{
		l = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		if (write(1, cmd->argv[i], ft_strlen(cmd->argv[i])) == -1)
			return (1);
		if (cmd->argv[i + 1])
			if (write(1, " ", 1) == -1)
				return (1);
		i++;
	}
	if (l)
		if (write(1, "\n", 1) == -1)
			return (1);
	return (0);
}

bool	ft_n_flag(char *str)
{
	int	i;

	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == (int)ft_strlen(str))
			return (1);
	}
	return (0);
}
