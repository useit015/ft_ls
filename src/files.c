/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 23:16:39 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/14 02:50:33 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

static int	ft_intlen(long long int n)
{
	int		i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

static int	max(int a, int b)
{
	return (a >= b ? a : b);
}

static void	init_max(t_max *m)
{
	m->link = 0;
	m->user = 0;
	m->group = 0;
	m->size = 0;
	m->time = 0;
}

static void	set_max(t_max *m, t_dir *d)
{
	m->link = max(ft_intlen(d->fs->st_nlink), m->link);
	m->user = max(ft_strlen(d->p->pw_name), m->user);
	m->group = max(ft_strlen(d->g->gr_name), m->group);
	m->size = max(ft_intlen(d->fs->st_size), m->size);
}

void	get_stat(t_dir *d, t_args *a, t_options *o, t_max *m)
{
	char *path;
	char *tmp;

	init_max(m);
	a->total = 0;
	tmp = ft_strjoin(a->arg, "/");
	while (d && d->dirent)
	{
		path = ft_strjoin(tmp, d->dirent->d_name);
		d->fs = (t_stat *)malloc(sizeof(t_stat));
		if (d->dirent->d_type == DT_LNK)
		{
			if (lstat(path, d->fs) < 0)
				return ;
			d->link_target = (char *)malloc(sizeof(char) * (d->fs->st_size + 1));
			if (readlink(path, d->link_target, d->fs->st_size) == -1)
				return ;
		}
		else if (stat(path, d->fs) < 0)
				return ;
		d->p = getpwuid(d->fs->st_uid);
		d->g = getgrgid(d->fs->st_gid);
		if (o->a || d->dirent->d_name[0] != '.')
		{
			set_max(m, d);
			a->total += d->fs->st_blocks;
		}
		free(path);
		d = d->next;
	}
	free(tmp);
}
