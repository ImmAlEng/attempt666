/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:46:31 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:46:32 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_heredoc_expand(t_data *data, char *line)
{
	t_dlist		node;
	t_dlist		*tok;
	t_expand	e;

	node.content = line;
	node.prev = NULL;
	node.next = NULL;
	tok = &node;
	e.str = (char *)tok->content;
	e.start = e.str;
	while (*e.start)
	{
		if (*e.start == '$' && ft_should_expand_dollar(e.start))
		{
			if (!ft_expand_dq(&e, data, &tok))
				return (free(tok->content), NULL);
			e.str = (char *)tok->content;
		}
		else
			e.start++;
	}
	return ((char *)tok->content);
}
