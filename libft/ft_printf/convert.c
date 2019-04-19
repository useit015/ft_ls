/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 18:43:39 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/20 00:25:23 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle.h"

char		*convert_char(t_param *arg, va_list ap)
{
	char	*s;
	char	c;

	s = (char*)ft_strnew(3);
	c = va_arg(ap, int);
	if (!c)
	{
		arg->null = 1;
		c = '|';
	}
	*s = c;
	return (s);
}

char		*convert_wchar(t_param *arg, va_list ap)
{
	wchar_t		uni;
	char		*s;

	uni = va_arg(ap, wchar_t);
	if (uni < 0 || (uni >= 0xd800 && uni < 0xe000) ||
		uni > 0x10ffff || (uni >= 256 && MB_CUR_MAX == 1))
		arg->err = 1;
	s = ft_strnew(5);
	s = ft_unitoa(uni, s);
	if (!*s)
	{
		arg->null = 1;
		*s = '|';
	}
	return (s);
}

char		*convert_wstr(t_param *arg, va_list ap)
{
	int			i;
	char		*s;
	size_t		max;
	size_t		len;
	wchar_t		*uni;

	i = 0;
	s = ft_strnew(5);
	uni = va_arg(ap, wchar_t *);
	max = (size_t)arg->precision;
	while (uni && uni[i])
	{
		len = ft_strlen(ft_unitoa(uni[i], s));
		if (len <= max)
		{
			max -= len;
			if (uni[i] < 0 || (uni[i] >= 0xd800 && uni[i] < 0xe000) ||
				uni[i] > 0x10ffff || (uni[i] >= 256 && MB_CUR_MAX == 1))
				arg->err = 1;
		}
		i++;
	}
	s = ft_unistrtoa(uni, arg->precision);
	return (s);
}

char		*convert_float(t_param *arg, va_list ap)
{
	if (arg->precision == -1)
		arg->precision = 6;
	if (ft_strchr("fF", arg->f))
		return (ft_ftoa(va_arg(ap, double), arg->precision));
	else if (arg->f == 'e')
		return (ft_ftoea(va_arg(ap, double), arg->precision, 'e'));
	else
		return (ft_ftoea(va_arg(ap, double), arg->precision, 'E'));
}

char		*convert_arg(char *f, va_list ap, t_param *arg, char *base)
{
	char		*s;

	if (ft_strchr("fFeE", *f))
		s = convert_float(arg, ap);
	else if (*f == 'p' && (arg->hash = 1))
		s = ft_convert_base(va_arg(ap, unsigned long), get_base('x'));
	else if (*f == 'd' || *f == 'i' || *f == 'D')
		s = convert_int(f, arg, ap);
	else if (*f == 'S' || (*f == 's' && arg->l))
		s = convert_wstr(arg, ap);
	else if (*f == 's')
		s = ft_strdup(va_arg(ap, char *));
	else if (*f == 'C' || (*f == 'c' && arg->l))
		s = convert_wchar(arg, ap);
	else if (*f == 'c')
		s = convert_char(arg, ap);
	else if (*f == '%')
		s = "%";
	else if (*f == 'u' || *f == 'U')
		s = convert_uint(f, arg, ap);
	else
		s = convert_b(f, arg, ap, base);
	if (!s)
		s = ft_strdup("(null)");
	return (s);
}
