/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 03:37:51 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/24 05:43:39 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

static void	fill_options_2(t_o *o, char f)
{
	if (f == 'd')
		o->d = 1;
	else if (f == 'g')
	{
		o->g = 1;
		o->l = 1;
	}
	else if (f == 'o')
	{
		o->o = 1;
		o->l = 1;
	}
	else if (f == 'S')
	{
		o->ss = 1;
		o->t = 0;
	}
	else if (f == 'f')
	{
		o->f = 1;
		o->a = 1;
	}
}

static void	fill_options_1(t_o *o, char f)
{
	if (f == 'c')
	{
		o->u = 0;
		o->c = 1;
		o->uu = 0;
	}
	else if (f == 'u')
	{
		o->u = 1;
		o->c = 0;
		o->uu = 0;
	}
	else if (f == 'U')
	{
		o->u = 0;
		o->c = 0;
		o->uu = 1;
	}
	else if (f == 't')
		o->t = 1;
	else if (f == 'T')
		o->tt = 1;
	else
		fill_options_2(o, f);
}

static void	fill_options(t_o *o, char f)
{
	if (f == 'l')
		o->l = 1;
	else if (f == 'r')
		o->r = 1;
	else if (f == 'R')
		o->rr = 1;
	else if (f == 'a')
		o->a = 1;
	else if (f == 'A')
		o->aa = 1;
	else if (f == 'F')
		o->ff = 1;
	else if (f == 'p')
	{
		o->p = 1;
		o->ff = 0;
	}
	else if (f == '1')
		o->l = 0;
	else
		fill_options_1(o, f);
}

static int	parse_chars(char *s, t_o *o)
{
	while (*s)
	{
		if (!ft_strchr("aAfFrRSgtldopuUcT1", *s))
		{
			o->illegal = *s;
			return (0);
		}
		fill_options(o, *s);
		s++;
	}
	return (1);
}

int			parse_options(int ac, char **av, t_o *o)
{
	int		i;

	i = 0;
	init_o(o);
	while (++i < ac)
	{
		if (*av[i] == '-' && *(av[i] + 1))
		{
			if (!ft_strcmp(av[i], "--"))
			{
				i++;
				break ;
			}
			(av[i])++;
		}
		else
			break ;
		if (!parse_chars(av[i], o))
			return (-1);
	}
	o->many = ac - i;
	return (i);
}
