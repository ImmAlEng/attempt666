/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:17:49 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 15:17:52 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_dlstadd_back(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*p;

	if (!new || !dlst)
		return ;
	if (!*dlst)
	{
		*dlst = new;
		return ;
	}
	p = ft_dlstlast(*dlst);
	p->next = new;
	new->prev = p;
}
