/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:52:45 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:52:46 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_strip_quotes(char **content)
{
	char	*old;
	char	*newstr;
	size_t	i;
	size_t	j;

	if (!content || !*content)
		return (false);
	old = *content;
	newstr = malloc(ft_strlen(old) + 1);
	if (!newstr)
		return (false);
	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] != '\'' && old[i] != '"')
			newstr[j++] = old[i];
		i++;
	}
	newstr[j] = '\0';
	free(old);
	*content = newstr;
	return (true);
}

static bool	ft_redir_unlink_pair(t_dlist **it, t_dlist **tokens, t_dlist **op,
		t_dlist **target)
{
	*op = *it;
	*target = (*op)->next;
	if (!*target || ft_is_operator((char *)(*target)->content))
		return (false);
	*it = (*target)->next;
	ft_dlst_unwrap(tokens, *op);
	ft_dlst_unwrap(tokens, *target);
	return (true);
}

static bool	ft_redir_attach(t_cmd *cmd, t_dlist *op, t_dlist *target)
{
	t_redir	*redir;
	t_dlist	*rnode;

	redir = ft_redir_new();
	if (!redir)
		return (ft_dlstdelone(op, free), ft_dlstdelone(target, free), false);
	redir->type = ft_get_redir_type((char *)op->content);
	if (redir->type == R_MAX)
		return (ft_free_redirs(&cmd->redirs), ft_dlstdelone(op, free),
			ft_dlstdelone(target, free), false);
	redir->quoted = (ft_strchr((char *)target->content, '\'')
			|| ft_strchr((char *)target->content, '"'));
	if (redir->type == R_HEREDOC && redir->quoted
		&& !ft_strip_quotes((char **)&target->content))
		return (ft_free((void **)&redir), ft_dlstdelone(op, free),
			ft_dlstdelone(target, free), false);
	ft_dlstdelone(op, free);
	ft_dlstadd_back(&redir->tokens, target);
	rnode = ft_dlstnew(redir);
	if (!rnode)
		return (ft_free_redirs(&cmd->redirs), false);
	ft_dlstadd_back(&cmd->redirs, rnode);
	return (true);
}

bool	ft_redir_init(t_cmd *cmd, t_dlist **tokens)
{
	t_dlist	*it;
	t_dlist	*op;
	t_dlist	*target;

	if (!cmd || !tokens)
		return (false);
	it = *tokens;
	while (it)
	{
		if (!ft_is_operator((char *)it->content))
		{
			it = it->next;
			continue ;
		}
		if (!ft_redir_unlink_pair(&it, tokens, &op, &target))
			return (false);
		if (!ft_redir_attach(cmd, op, target))
			return (false);
	}
	return (true);
}
