/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_strtoll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imengels <imengels@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:48:00 by imengels          #+#    #+#             */
/*   Updated: 2026/04/12 18:38:20 by imengels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_skip_spaces(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace((unsigned char)s[i]))
		i++;
	return (i);
}

static int	ft_read_sign(const char *s, int *i)
{
	int	sign;

	sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static bool	ft_parse_digits(const char *s, int *i, int sign,
		unsigned long long *acc)
{
	unsigned long long	lim;
	int					d;

	if (!ft_isdigit((unsigned char)s[*i]))
		return (false);
	lim = (unsigned long long)ft_llmax() + (unsigned long long)(sign < 0);
	while (ft_isdigit((unsigned char)s[*i]))
	{
		d = s[*i] - '0';
		if (*acc > (lim - (unsigned long long)d) / 10ULL)
			return (false);
		*acc = (*acc * 10ULL) + (unsigned long long)d;
		(*i)++;
	}
	return (true);
}

static bool	ft_only_trailing_space(const char *s, int i)
{
	while (s[i] && ft_isspace((unsigned char)s[i]))
		i++;
	return (s[i] == '\0');
}

long long	ft_my_strtoll(const char *nptr, bool *ok)
{
	unsigned long long	acc;
	int					i;
	int					sign;

	if (!nptr)
		return (0);
	acc = 0;
	if (ok)
		*ok = false;
	i = ft_skip_spaces(nptr);
	sign = ft_read_sign(nptr, &i);
	if (!ft_parse_digits(nptr, &i, sign, &acc))
		return (0);
	if (!ft_only_trailing_space(nptr, i))
		return (0);
	if (ok)
		*ok = true;
	if (sign < 0 && acc == (unsigned long long)ft_llmax() + 1ULL)
		return (ft_llmin());
	return ((long long)acc * (long long)sign);
}
