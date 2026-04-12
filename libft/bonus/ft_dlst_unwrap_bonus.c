/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_unwrap_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:16:43 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 15:16:44 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_dlist	*ft_dlst_unwrap(t_dlist **head, t_dlist *node)
{
	if (!head || !*head || !node)
		return (NULL);
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
