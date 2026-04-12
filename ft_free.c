/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:45:30 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:45:31 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_if(int *fd)
{
	if (!fd)
		return ;
	if (*fd > 2)
		close(*fd);
	*fd = -1;
}

void	ft_free_data(t_data **data)
{
	if (!data || !*data)
		return ;
	ft_free((void **)&(*data)->line);
	(*data)->pipeline = NULL;
	if ((*data)->cmds)
		ft_free_cmds(*data);
	if ((*data)->env)
		ft_free_arrp(&(*data)->env);
	ft_free((void **)data);
	rl_clear_history();
}
