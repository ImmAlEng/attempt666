/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imengels <imengels@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:34:37 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 20:24:25 by imengels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_exit_parse_number(char *s, long long *n)
{
	bool	ok;

	if (!s || !n)
		return (false);
	*n = ft_my_strtoll(s, &ok);
	if (!ok)
		return (false);
	return (true);
}

static int	ft_exit_code(long long n)
{
	return ((int)(n % 256 + 256) % 256);
}

int	ft_exit(t_data *data, int cmd_i)
{
	long long	n;

	write(1, "exit\n", 5);
	if (!data->cmds[cmd_i]->argv[1])
	{
		data->quit = true;
		return (g_exit_status);
	}
	if (!ft_exit_parse_number(data->cmds[cmd_i]->argv[1], &n))
		return (ft_err_with_arg("exit: ", "numeric argument required"),
			data->quit = true, 2);
	if (data->cmds[cmd_i]->argv[2])
		return (ft_err_with_arg("exit: ", "too many arguments"), 1);
	data->quit = true;
	return (ft_exit_code(n));
}

void	ft_free_exit(t_data *data, int e_c)
{
	ft_free_data(&data);
	exit (e_c);
}
