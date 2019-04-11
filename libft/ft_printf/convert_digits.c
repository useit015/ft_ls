/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_digits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 03:49:47 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:45:13 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle.h"

char		*convert_int(char *f, t_param *arg, va_list ap)
{
	long int	i;

	if (arg->ll)
		return (ft_lltoa(va_arg(ap, long long int)));
	else if (arg->l || *f == 'D')
		return (ft_ltoa(va_arg(ap, long int)));
	else if (arg->j)
		return (ft_jtoa(va_arg(ap, intmax_t)));
	else if (arg->z)
	{
		i = va_arg(ap, long int);
		if (i < 0)
			return (ft_ltoa(i));
		else
			return (ft_ztoa(i));
	}
	else if (arg->h)
		return (ft_htoa((short)va_arg(ap, int)));
	else if (arg->hh)
		return (ft_hhtoa((signed char)va_arg(ap, int)));
	else
		return (ft_itoa(va_arg(ap, int)));
}

char		*convert_uint(char *f, t_param *arg, va_list ap)
{
	if (arg->ll)
		return (ft_ulltoa(va_arg(ap, unsigned long long int)));
	else if (arg->l || *f == 'U')
		return (ft_ulltoa(va_arg(ap, unsigned long int)));
	else if (arg->j)
		return (ft_ujtoa(va_arg(ap, uintmax_t)));
	else if (arg->z)
		return (ft_ztoa(va_arg(ap, size_t)));
	if (arg->hh)
		return (ft_utoa((unsigned char)va_arg(ap, unsigned int)));
	else if (arg->h)
		return (ft_uhtoa((unsigned short)va_arg(ap, int)));
	else
		return (ft_utoa(va_arg(ap, unsigned int)));
}

char		*convert_b(char *f, t_param *arg, va_list ap, char *base)
{
	if (arg->ll)
		return (ft_convert_base(va_arg(ap, unsigned long long int), base));
	else if (arg->l || *f == 'O')
		return (ft_convert_base(va_arg(ap, unsigned long int), base));
	else if (arg->j)
		return (ft_convert_base(va_arg(ap, uintmax_t), base));
	else if (arg->z)
		return (ft_convert_base(va_arg(ap, size_t), base));
	if (arg->hh)
		return (ft_convert_base((unsigned char)va_arg(ap, unsigned int), base));
	else if (arg->h)
		return (ft_convert_base((unsigned short)va_arg(ap, int), base));
	else
		return (ft_convert_base(va_arg(ap, unsigned int), base));
}
