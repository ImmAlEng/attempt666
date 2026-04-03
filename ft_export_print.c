#include "minishell.h"

int	ft_print_export_var(char **env)
{
	char	**sorted_env;
	int		r;

	sorted_env = ft_sort_env(env);
	if (!sorted_env)
		return (1);
	r = ft_actual_export_print(sorted_env);
	return (free(sorted_env), r);
}

int	ft_actual_export_print(char **env)
{
	int	i;
	int	j;
	int	eq_fl;

	i = -1;
	while (env[++i])
	{
		eq_fl = 0;
		write (1, "declare -x ", 11);
		j = -1;
		while (env[i][++j])
		{
			write (1, &env[i][j], 1);
			if ((env[i][j] == '=' && eq_fl == 0) || env[i][j + 1] == '\0')
			{
				write (1, "\"", 1);
				eq_fl = 1;
			}
		}
		write (1, "\n", 1);
	}
	return (0);
}

char	**ft_sort_env(char **env)
{
	char	**sorted_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	sorted_env = malloc(sizeof(char *) * (i + 1));
	if (!sorted_env)
		return (NULL);
	i = -1;
	while (env[++i])
		sorted_env[i] = env[i];
	sorted_env[i] = NULL;
	return (ft_bubble_sort(sorted_env));
}

char	**ft_bubble_sort(char **env)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	size = 0;
	while (env[size])
		size++;
	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (ft_cmp_export(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
		}
	}
	return (env);
}

int	ft_cmp_export(char *s1, char *s2)
{
	int	i;
	int	c1;
	int	c2;

	if (s1[0] == '_' && s2[0] != '_')
		return (1);
	if (s1[0] != '_' && s2[0] == '_')
		return (-1);
	if (s1[0] == '_' && s2[0] == '_')
		return (ft_cmp_export(s1 + 1, s2 + 1));
	i = -1;
	while (s1[++i] && s2[i])
	{
		if (s1[i] == '=' || s2[i] == '=')
			break ;
		c1 = ft_tolower(s1[i]);
		c2 = ft_tolower(s2[i]);
		if (c1 != c2)
			return (c1 - c2);
	}
	if (s1[i] == '=' && s2[i] != '=')
		return (-1);
	if (s1[i] != '=' && s2[i] == '=')
		return (1);
	return (0);
}
