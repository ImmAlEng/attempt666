/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match_found.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:46:56 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:46:58 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_match_found(char *c)
{
	size_t	i;
	char	q;

	if (!c || !*c)
		return (false);
	q = *c;
	i = 0;
	while (c[++i])
		if (c[i] == q)
			return (true);
	return (false);
}
