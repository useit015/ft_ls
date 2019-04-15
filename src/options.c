/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 03:37:51 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/14 22:39:19 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

static void	init_options(t_options *o)
{
	o->l = 0;
	o->t = 0;
	o->g = 0;
	o->r = 0;
	o->rr = 0;
	o->a = 0;
	o->aa = 0;
	o->f = 0;
	o->ff = 0;
}

static void	fill_options(t_options *o, char f)
{
	if (f == 'l')
		o->l = 1;
	else if (f == 't')
		o->t = 1;
	else if (f == 'g')
		o->g = 1;
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
}

int			parse_options(int ac, char **av, t_options *o)
{
	int		i;

	i = 0;
	init_options(o);
	while (++i < ac)
	{
		if (*av[i] == '-')
			(av[i])++;
		else
			break ;
		while (*av[i])
		{
			fill_options(o, *av[i]);
			(av[i])++;
		}
	}
	o->many = ac - i;
	return (i);
}
