/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_dq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:34:46 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:40:51 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_superglue_dq(t_dlist **tok, char *value, size_t start,
		char **stop)
{
	char	*pre;
	char	*suf;
	char	*tmp;

	if (!tok || !*tok || !value || !stop || !*stop)
		return (free(value), false);
	pre = ft_substr((char *)(*tok)->content, 0, start);
	suf = ft_strdup(*stop);
	if (!pre || !suf)
		return (free(pre), free(suf), free(value), false);
	tmp = ft_strjoin(pre, value);
	if (!tmp || !ft_replace_content(*tok, ft_strjoin(tmp, suf)))
		return (free(pre), free(suf), free(tmp), free(value), false);
	*stop = (char *)(*tok)->content + ft_strlen(pre) + ft_strlen(value);
	return (free(pre), free(suf), free(tmp), free(value), true);
}

bool	ft_expand_dq(t_expand *e, t_data *data, t_dlist **tok)
{
	e->stop = e->start + 1;
	e->name = ft_get_varname(e->str, &e->stop);
	if (!e->name)
		return (false);
	e->val = ft_getenv(e->name, data->env);
	if (!e->val)
		return (free(e->name), false);
	if (!ft_superglue_dq(tok, e->val, (size_t)(e->start - e->str), &e->stop))
		return (free(e->name), false);
	e->start = e->stop;
	e->str = (char *)(*tok)->content;
	return (free(e->name), true);
}

char	ft_is_quoted(char *c, char *q, bool init)
{
	if (init)
		*q = 0;
	else
	{
		if (*q && *q == *c)
			*q = 0;
		else if (!*q && (*c == '\'' || *c == '\"') && ft_match_found(c))
			*q = *c;
	}
	return (*q);
}
