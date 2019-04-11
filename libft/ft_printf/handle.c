/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 05:52:37 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:44:47 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle.h"

static void	display(char *s, int nu, char *cut, t_buff *b)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	write(1, b->buff, b->i);
	b->ret += b->i;
	b->i = 0;
	if (nu)
	{
		len = ft_strlen(s);
		while (s[++i] != '|' && i < len)
			;
		s[i] = 0;
	}
	else
	{
		tmp = s;
		s = ft_strjoin(cut, s);
		len = ft_strlen(s);
	}
	write(1, s, len);
	b->ret += len;
	ft_memset(b->buff, 0, BUFF_SIZE);
}

static int	buff_is_null(char *s)
{
	while (*s)
	{
		if (*s != 48 && *s != ' ')
			return (0);
		s++;
	}
	return (1);
}

static void	format(char *s, t_param *arg, char *cut, t_buff *b)
{
	int		len;

	len = (int)ft_strlen(s);
	s = handle_precision(arg, s, len);
	len = (int)ft_strlen(s);
	s = handle_width(arg, s, len);
	s = handle_plus_space(arg, s, len);
	if (!buff_is_null(s) || arg->f == 'p')
		s = handle_hash(arg, s, len);
	display(s, arg->null, cut, b);
}

int			handler(char *f, va_list ap, char *cut, t_buff *b)
{
	int		i;
	char	*s;
	t_param	arg;

	init_arg(&arg);
	parse_flags(f, &arg, ap);
	f = skip_flags(f);
	if (*f)
	{
		if (is_fspec(*f))
			s = convert_arg(f, ap, &arg, get_base(*f));
		else
			s = new_fspec(&arg, *f);
		if (arg.err)
			return (0);
		format(s, &arg, cut, b);
		if ((i = get_next_spec(++f)) > BUFF_SIZE - b->i)
		{
			write(1, f, i);
			return (handler(f + i + 1, ap, "", b));
		}
		if (buff_cpy(f, i, ap, b) == 0)
			return (0);
	}
	return (1);
}
