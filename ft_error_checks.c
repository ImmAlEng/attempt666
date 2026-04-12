/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:12:11 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:12:12 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_has_ambiguous_redirect(t_cmd **cmds)
{
	t_dlist	*rnode;
	t_redir	*r;
	size_t	i;

	if (!cmds)
		return (false);
	i = 0;
	while (cmds[i])
	{
		rnode = cmds[i]->redirs;
		while (rnode)
		{
			r = (t_redir *)rnode->content;
			if (!r || !r->tokens || !r->tokens->content || r->tokens->next
				|| !*((char *)r->tokens->content))
				return (true);
			rnode = rnode->next;
		}
		i++;
	}
	return (false);
}
