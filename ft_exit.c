#include "minishell.h"

int	ft_exit(t_data *data, int cmd_i)
{
	char	**argv;
	long	code;
	int		i;

	argv = data->cmds[cmd_i]->argv;
	write(1, "exit\n", 5);
	if (!argv[1])
	{
		data->quit = true;
		return (g_exit_status);
	}
	i = 0;
	while (argv[1][i])
	{
		if (!ft_isdigit((unsigned char)argv[1][i])
			&& !(i == 0 && (argv[1][0] == '-' || argv[1][0] == '+')))
			return (ft_err_with_arg("exit: ", "numeric argument required"),
				data->quit = true, 2);
		i++;
	}
	if (argv[2])
		return (ft_err_with_arg("exit: ", "too many arguments"), 1);
	code = 0;
	i = 0;
	if (argv[1][i] == '+' || argv[1][i] == '-')
		i++;
	while (argv[1][i])
		code = code * 10 + (argv[1][i++] - '0');
	if (argv[1][0] == '-')
		code = -code;
	data->quit = true;
	return ((int)(code % 256 + 256) % 256);
}
