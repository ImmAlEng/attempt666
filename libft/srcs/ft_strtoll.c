/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amkhuder <amkhuder@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:12:38 by amkhuder          #+#    #+#             */
/*   Updated: 2026/04/12 14:12:39 by amkhuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <errno.h>

static const char	*ft_skip_space(const char *s)
{
	while (s && ft_isspace((unsigned char)*s))
		s++;
	return (s);
}

static const char	*ft_parse_sign(const char *s, int *sign)
{
	*sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			*sign = -1;
		s++;
	}
	return (s);
}

static int	ft_push_digit(unsigned long long *n,
		char c, unsigned long long lim)
{
	unsigned long long	d;

	d = (unsigned long long)(c - '0');
	if (*n > (lim - d) / 10ULL)
		return (0);
	*n = (*n * 10ULL) + d;
	return (1);
}

static long long	ft_error_ret(const char *p, char **endptr,
		int err, int sign)
{
	if (err)
		errno = err;
	if (endptr)
		*endptr = (char *)p;
	if (err == ERANGE && sign < 0)
		return (ft_llmin());
	if (err == ERANGE)
		return (ft_llmax());
	return (0);
}

long long	ft_strtoll(const char *nptr, char **endptr, int base)
{
	unsigned long long	n;
	unsigned long long	lim;
	const char			*cur;
	int					sign;

	if (base != 10)
		return (ft_error_ret(nptr, endptr, EINVAL, 1));
	cur = ft_parse_sign(ft_skip_space(nptr), &sign);
	if (!ft_isdigit((unsigned char)*cur))
		return (ft_error_ret(nptr, endptr, 0, sign));
	n = 0;
	lim = (unsigned long long)ft_llmax() + (sign < 0);
	while (ft_isdigit((unsigned char)*cur))
	{
		if (!ft_push_digit(&n, *cur, lim))
			return (ft_error_ret(cur, endptr, ERANGE, sign));
		cur++;
	}
	if (endptr)
		*endptr = (char *)cur;
	if (sign < 0 && n == (unsigned long long)ft_llmax() + 1ULL)
		return (ft_llmin());
	return ((long long)n * (long long)sign);
}
