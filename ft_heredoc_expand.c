#include "minishell.h"

static char	*ft_append_part(char *dst, const char *part, size_t len)
{
	char	*chunk;
	char	*joined;

	chunk = ft_substr((char *)part, 0, len);
	if (!chunk)
		return (free(dst), NULL);
	joined = ft_strjoin(dst, chunk);
	free(dst);
	free(chunk);
	return (joined);
}

static char	*ft_expand_value(t_data *data, char *name)
{
	if (!ft_strcmp(name, "?"))
		return (ft_itoa(g_exit_status));
	return (ft_getenv(name, data->env));
}

static bool	ft_add_char(char **res, char **p)
{
	char	*end;

	end = ft_append_part(*res, *p, 1);
	if (!end)
		return (false);
	*res = end;
	(*p)++;
	return (true);
}

static bool	ft_expand_dollar(t_data *data, char **res, char **p, char *line)
{
	char	*end;
	char	*name;
	char	*val;

	end = *p + 1;
	name = ft_get_varname(line, &end);
	if (!name)
		return (false);
	if (!*name)
		*res = ft_append_part(*res, "$", 1);
	else
	{
		val = ft_expand_value(data, name);
		if (!val)
			return (free(name), false);
		*res = ft_append_part(*res, val, ft_strlen(val));
		free(val);
	}
	free(name);
	if (!*res)
		return (false);
	*p = end;
	return (true);
}

char	*ft_heredoc_expand(t_data *data, char *line)
{
	char	*res;
	char	*p;

	res = ft_strdup("");
	p = line;
	if (!res)
		return (free(line), NULL);
	while (*p)
	{
		if (*p == '$' && !ft_expand_dollar(data, &res, &p, line))
			return (free(res), free(line), NULL);
		if (*p != '$' && !ft_add_char(&res, &p))
			return (free(line), NULL);
	}
	return (free(line), res);
}
