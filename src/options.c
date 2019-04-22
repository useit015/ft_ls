/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 03:37:51 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/22 04:11:32 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

static void	init_options(t_options *o)
{
	o->l = 0;
	o->t = 0;
	o->c = 0;
	o->d = 0;
	o->p = 0;
	o->g = 0;
	o->o = 0;
	o->r = 0;
	o->a = 0;
	o->f = 0;
	o->u = 0;
	o->aa = 0;
	o->rr = 0;
	o->ff = 0;
	o->uu = 0;
	o->ss = 0;
	o->tt = 0;
}

static void	fill_options(t_options *o, char f)
{
	if (f == 'l')
		o->l = 1;
	else if (f == '1')
		o->l = 0;
	else if (f == 't')
		o->t = 1;
	else if (f == 'c')
	{
		o->u = 0;
		o->c = 1;
		o->uu = 0;
	}
	else if (f == 'd')
		o->d = 1;
	else if (f == 'p')
	{
		o->p = 1;
		o->ff = 0;
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
	else if (f == 'r')
		o->r = 1;
	else if (f == 'R')
		o->rr = 1;
	else if (f == 'a')
		o->a = 1;
	else if (f == 'A')
		o->aa = 1;
	else if (f == 'f')
	{
		o->f = 1;
		o->a = 1;
	}
	else if (f == 'F')
		o->ff = 1;
	else if (f == 'T')
		o->tt = 1;
	else if (f == 'S')
	{
		o->ss = 1;
		o->t = 0;
	}
}

int			parse_options(int ac, char **av, t_options *o)
{
	int		i;

	i = 0;
	init_options(o);
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
		while (*av[i])
		{
			if (!ft_strchr("aAfFrRSgtldopuUcT1", *av[i]))
			{
				o->illegal = *av[i];
				return (-1);
			}
			fill_options(o, *av[i]);
			(av[i])++;
		}
	}
	o->many = ac - i;
	return (i);
}
