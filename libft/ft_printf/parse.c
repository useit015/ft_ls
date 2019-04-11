/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 00:50:31 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:44:38 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle.h"

void		parse_precision(char **f, t_param *arg)
{
	while (**f == '.')
		(*f)++;
	arg->precision = ft_atoi(*f);
	if (!ft_isdigit(**f))
		(*f)--;
	while (ft_isdigit(**f))
		(*f)++;
}

void		parse_width(char **f, t_param *arg)
{
	arg->width = ft_atoi(*f);
	while (ft_isdigit(**f))
		(*f)++;
}

void		parse_mods(char **f, t_param *arg)
{
	if (**f == 'l' && *((*f) + 1) == 'l')
	{
		(*f)++;
		arg->ll = 1;
	}
	else if (**f == 'h' && *((*f) + 1) == 'h')
	{
		(*f)++;
		arg->hh = 1;
	}
	else if (**f == 'l')
		arg->l = 1;
	else if (**f == 'h')
		arg->h = 1;
	else if (**f == 'z')
		arg->z = 1;
	else if (**f == 'j')
		arg->j = 1;
}

void		parse_star(t_param *arg, va_list ap)
{
	int i;

	i = va_arg(ap, int);
	if (i < 0 && arg->precision == -1)
	{
		arg->minus = 1;
		i = -i;
	}
	if (arg->precision == -1)
		arg->width = i;
	else
		arg->precision = i;
}

void		parse_flags(char *f, t_param *arg, va_list ap)
{
	while (is_flag(*f))
	{
		if (*f != 48 && ft_isdigit(*f))
			parse_width(&f, arg);
		if (*f == '*')
			parse_star(arg, ap);
		else if (*f == '#')
			arg->hash = 1;
		else if (*f == '-')
			arg->minus = 1;
		else if (*f == '+')
			arg->plus = 1;
		else if (*f == '0')
			arg->zero = 1;
		else if (*f == ' ')
			arg->space = 1;
		else if (*f == '.' && arg->precision == -1)
			parse_precision(&f, arg);
		parse_mods(&f, arg);
		if (is_fspec(*f))
			break ;
		f++;
	}
	if (is_fspec(*f))
		arg->f = *f;
}
