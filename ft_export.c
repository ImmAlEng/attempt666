#include "minishell.h"

int	ft_export(t_data *data, int cmd_i)
{
	int	i;
	int	env_i;

	if (!data->cmds[cmd_i]->argv[1])
		return (ft_print_export_var(data->env));
	else
	{
		i = 0;
		while (data->cmds[cmd_i]->argv[++i])
		{
			if (ft_export_valid(data->cmds[cmd_i]->argv[i]))
			{
				env_i = ft_var_present(data, data->cmds[cmd_i]->argv[i]);
				if (env_i != -1)
					ft_modify_var(data, data->cmds[cmd_i]->argv[i], env_i);
				else
					ft_add_var(data, data->cmds[cmd_i]->argv[i]);
			}
			else
				return (write(2, "arg not valid\n", 14), 1);
		}
		return (0);
	}
}
