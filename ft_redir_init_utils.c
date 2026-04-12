/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_init_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:51:01 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:51:16 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_get_redir(t_dlist *node)
{
	if (!node || !node->content)
		return (NULL);
	return ((t_redir *)node->content);
}

t_redir	*ft_redir_new(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	ft_bzero(redir, sizeof(t_redir));
	redir->type = R_MAX;
	return (redir);
}
