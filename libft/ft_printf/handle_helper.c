/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 05:41:51 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:45:00 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle.h"

static char	*expand_str(t_param *arg, char *s, int len, char c)
{
	int		i;
	int		sign;
	char	*tmp;

	i = 0;
	sign = 0;
	tmp = ft_strnew(arg->width);
	if (arg->minus)
	{
		copy_arg_str(s, tmp, &i);
		while (i < arg->width)
			tmp[i++] = c;
	}
	else
	{
		sign = is_negative(arg, &s, &len);
		while (i < arg->width - len)
			tmp[i++] = c;
		copy_arg_str(s, tmp, &i);
		if (sign)
			tmp[0] = '-';
	}
	tmp[i] = 0;
	return (tmp);
}

char		*handle_width(t_param *arg, char *s, int len)
{
	char	c;

	if (!ft_strchr("%fF", arg->f) && !arg->null && (arg->precision > 0 ||
		(arg->precision > -1 && ft_strchr("diDuUoOxXp", arg->f))) && arg->zero)
		arg->zero = 0;
	c = get_fill(arg);
	if (arg->width > len)
		s = expand_str(arg, s, len, c);
	return (s);
}

char		*handle_hash(t_param *a, char *s, int len)
{
	int		i;
	char	*tmp;

	if (*s && a->hash && ft_strchr("xXoOp", a->f))
	{
		i = -1;
		while (s[++i] == 32)
			;
		if (!a->minus && !a->zero && i > 0)
		{
			if (ft_strchr("oO", a->f))
				i--;
			else if (i > 1)
				i -= 2;
			else
				i--;
		}
		s = trim_arg(s, a, len);
		tmp = ft_strjoin(get_prefix(a->f), s + i);
		ft_strcpy(s + i, tmp);
		free(tmp);
	}
	if (a->f == 'p' && !*s)
		return (ft_strdup("0x"));
	return (s);
}

char		*handle_plus_space(t_param *arg, char *s, int len)
{
	int		i;
	char	c;
	char	*tmp;

	c = get_sign(arg);
	if (ft_strchr("diD", arg->f) && !ft_strchr(s, '-') &&
		(arg->plus || arg->space))
	{
		i = -1;
		tmp = ft_strnew(ft_strlen(s) + 2);
		while (s[++i] == 32)
			tmp[i] = s[i];
		tmp[i] = c;
		ft_strcpy(tmp + i + 1, s + i);
		tmp = trim_arg2(arg, tmp, c, len);
		s = tmp;
	}
	return (s);
}

char		*handle_precision(t_param *arg, char *s, int len)
{
	char	*tmp;

	if (arg->precision >= 0 && !arg->null)
	{
		if (ft_strchr("dDiuUoOxXp", arg->f) && ft_strchr(s, '-'))
			len--;
		if (((*s == '0' && !*(s + 1) && (!arg->hash ||
			!ft_strchr("oO", arg->f))) || arg->f == 's') && !arg->precision)
			s = ft_strnew(1);
		else if (ft_strchr("sSC", arg->f) && arg->precision < len)
			s = ft_strncpy(ft_strnew(arg->precision + 1), s, arg->precision);
		else if (ft_strchr("dDiuUoOxXp", arg->f) && arg->precision > len)
		{
			tmp = ft_memset(ft_strnew(arg->precision + 1), 48, arg->precision);
			if (*s != '-')
				ft_strcpy((tmp + arg->precision - len), s);
			else
			{
				*tmp = '-';
				ft_strcpy((tmp + arg->precision - len + 1), s + 1);
			}
			s = tmp;
		}
	}
	return (s);
}
