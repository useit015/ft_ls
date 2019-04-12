/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:49 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/12 04:28:13 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

void	 init_max(t_max *m)
{
	m->link = 0;
	m->user = 0;
	m->group = 0;
	m->size = 0;
	m->time = 0;
}

int		ft_intlen(long long int n)
{
	int		i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

void	set_max(t_max *m, t_dir *d)
{
	int	link_len;
	int	user_len;
	int	group_len;
	int	size_len;

	link_len = ft_intlen(d->fs->st_nlink);
	user_len = ft_strlen(d->p->pw_name);
	group_len = ft_strlen(d->g->gr_name);
	size_len = ft_intlen(d->fs->st_size);
	m->link = link_len > m->link ? link_len : m->link;
	m->user = user_len > m->user ? user_len : m->user;
	m->group = group_len > m->group ? group_len : m->group;
	m->size = size_len > m->size ? size_len : m->size;
}

void	get_stat(t_dir *d, t_max *m)
{
	init_max(m);
	while (d && d->dirent)
	{
		d->fs = (t_stat *)malloc(sizeof(t_stat));
		if (d->dirent->d_type == DT_LNK)
		{
			if (lstat(d->dirent->d_name, d->fs) < 0)
				return ;
			d->link_target = (char *)malloc(sizeof(char) * (d->fs->st_size + 1));
			if (readlink(d->dirent->d_name, d->link_target, d->fs->st_size + 1) == -1)
				return ;
		}
		else
		{
			if (stat(d->dirent->d_name, d->fs) < 0)
				return ;	
		}
		d->p = getpwuid(d->fs->st_uid);
		d->g = getgrgid(d->fs->st_gid);
		set_max(m, d);
		d = d->next;
	}
}

int		main(int ac, char **av)
{
	int			i;
	t_options	o;
	t_max		m;
	t_args		*a;
	t_dir		*d;

	i = parse_options(ac, av, &o);
	a = parse_args(ac, av, i);
	while (a && a->arg)
	{
		d = get_dir_content(a->arg);
		get_stat(d, &m);
		print_dir_content(d, a, &o, &m);
		a = a->next;
	}
	return (0);
}
