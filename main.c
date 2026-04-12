/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:06:17 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 15:06:20 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = ft_init_data(ac, av, env);
	if (!data)
		return (ft_cleanup_quit(NULL, true));
	ft_setup_signals();
	if (ft_prompt(data))
		return (ft_cleanup_quit(&data, data->malloc_err));
	return (ft_cleanup_quit(&data, data->malloc_err));
}
