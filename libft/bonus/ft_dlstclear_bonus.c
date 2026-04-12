/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:17:59 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 15:18:00 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_dlstclear(t_dlist **dlst, void (*del)(void *))
{
	t_dlist	*p1;
	t_dlist	*p2;

	if (!dlst || !del)
		return ;
	p1 = *dlst;
	while (p1)
	{
		p2 = p1;
		p1 = p1->next;
		ft_dlstdelone(p2, del);
	}
	*dlst = NULL;
}
