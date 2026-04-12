/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:49:04 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:49:05 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_env(t_data *data, int c_i)
{
	int	i;

	if (data->cmds[c_i]->argv[1])
		return (write(2, "too many args\n", 14), 127);
	i = -1;
	while (data->env[++i])
	{
		write(1, data->env[i], ft_strlen(data->env[i]));
		write(1, "\n", 1);
	}
	return (0);
}
