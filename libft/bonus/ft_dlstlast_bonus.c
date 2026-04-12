/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlast_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:18:20 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 15:18:21 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_dlist	*ft_dlstlast(t_dlist *dlst)
{
	t_dlist	*p;

	if (!dlst)
		return (NULL);
	p = dlst;
	while (p->next)
		p = p->next;
	return (p);
}
