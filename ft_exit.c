#include "minishell.h"

static bool	ft_exit_parse_number(char *s, long long *n)
{
	char	*end;

	if (!s || !n)
		return (false);
	while (ft_isspace((unsigned char)*s))
		s++;
	if (!*s)
		return (false);
	errno = 0;
	*n = strtoll(s, &end, 10);
	if (s == end || errno == ERANGE)
		return (false);
	while (ft_isspace((unsigned char)*end))
		end++;
	if (*end)
		return (false);
	return (true);
}

static int	ft_exit_code(long long n)
{
	return ((int)(n % 256 + 256) % 256);
}

int	ft_exit(t_data *data, int cmd_i)
{
	char	**argv;
	long long	n;

	argv = data->cmds[cmd_i]->argv;
	write(1, "exit\n", 5);
	if (!argv[1])
	{
		data->quit = true;
		return (g_exit_status);
	}
	if (!ft_exit_parse_number(argv[1], &n))
		return (ft_err_with_arg("exit: ", "numeric argument required"),
			data->quit = true, 2);
	if (argv[2])
		return (ft_err_with_arg("exit: ", "too many arguments"), 1);
	data->quit = true;
	return (ft_exit_code(n));
}
