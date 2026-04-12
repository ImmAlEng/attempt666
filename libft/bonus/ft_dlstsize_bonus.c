/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:18:32 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 15:18:32 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_dlstsize(t_dlist *dlst)
{
	int		size;
	t_dlist	*p;

	size = 0;
	p = dlst;
	if (!dlst)
		return (0);
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}
