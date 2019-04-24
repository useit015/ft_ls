/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 05:18:23 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/24 05:22:28 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

static int	max(int a, int b)
{
	return (a >= b ? a : b);
}

void		init_max(t_max *m)
{
	m->link = 0;
	m->user = 0;
	m->group = 0;
	m->size = 0;
	m->min = 0;
	m->maj = 0;
}

void		set_max(t_max *m, t_dir *d)
{
	m->link = max(ft_intlen(d->fs->st_nlink), m->link);
	m->user = max(ft_strlen(d->p->pw_name), m->user);
	m->group = max(ft_strlen(d->g->gr_name), m->group);
	m->size = max(ft_intlen(d->fs->st_size), m->size);
	m->maj = d->m ? max(ft_intlen(d->m->major), m->maj) : 0;
	m->min = d->m ? max(ft_intlen(d->m->minor), m->min) : 0;
	if (m->min || m->maj)
		m->size = m->min + m->maj + 3;
}

void		init_options(t_options *o)
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
