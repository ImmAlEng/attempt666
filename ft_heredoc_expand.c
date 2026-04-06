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
		if (*e.start == '$')
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
