/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_after.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:16:54 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 15:19:04 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_dlstadd_after(t_dlist *dlis, t_dlist *insert)
{
	if (!dlis || !insert)
		return ;
	insert->next = dlis->next;
	if (dlis->next)
		dlis->next->prev = insert;
	dlis->next = insert;
	insert->prev = dlis;
}
