/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 03:53:42 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:44:26 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle.h"

int			direct_print(char *f, int *i)
{
	int		j;

	j = ft_strlen(f);
	*i = get_next_spec(f);
	if (*i == j)
	{
		write(1, f, j);
		return (j);
	}
	return (0);
}

int			is_negative(t_param *arg, char **s, int *len)
{
	if (arg->zero && **s == '-')
	{
		*len -= 1;
		*s += 1;
		return (1);
	}
	return (0);
}

void		copy_arg_str(char *s, char *dst, int *i)
{
	while (*s)
	{
		dst[*i] = *s;
		s++;
		(*i)++;
	}
}

char		*trim_arg2(t_param *arg, char *s, char c, int len)
{
	if (arg->width > len)
	{
		if (arg->minus)
			s[ft_strlen(s) - 1] = 0;
		else
		{
			s++;
			if (*(s - 1) == c)
				*s = c;
		}
	}
	return (s);
}

char		*trim_arg(char *s, t_param *arg, int len)
{
	size_t slen;

	slen = ft_strlen(s);
	if (!arg->minus)
	{
		if ((arg->width > len || (arg->precision >= len && *s == 48))
			&& ft_strchr("oO", arg->f))
			s++;
		else if (arg->width - 1 > len)
			s += 2;
		else if (arg->width > len)
			s++;
	}
	else
	{
		if ((arg->width > len || arg->precision >= len)
			&& ft_strchr("oO", arg->f))
			s[slen - 1] = 0;
		else if (arg->width - 1 > len)
			s[slen - 2] = 0;
		else if (arg->width > len)
			s[slen - 1] = 0;
	}
	return (s);
}
