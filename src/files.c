/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 23:16:39 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/22 03:12:07 by onahiz           ###   ########.fr       */
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

void	init_max(t_max *m)
{
	m->link = 0;
	m->user = 0;
	m->group = 0;
	m->major = 0;
	m->minor = 0;
	m->size = 0;
}

void	set_max(t_max *m, t_dir *d)
{
	m->link = max(ft_intlen(d->fs->st_nlink), m->link);
	m->user = max(ft_strlen(d->p->pw_name), m->user);
	m->group = max(ft_strlen(d->g->gr_name), m->group);
	m->size = max(ft_intlen(d->fs->st_size), m->size);
	m->major = d->m ? max(ft_intlen(d->m->major), m->major) : 0;
	m->minor = d->m ? max(ft_intlen(d->m->minor), m->minor) : 0;
	m->size = max(m->minor + m->major + 1, m->size);
}

int		file_type(int t)
{
	return (t == DT_FIFO || t == DT_CHR || t == DT_BLK || t == DT_REG || t == DT_DIR || t == DT_LNK || t == DT_SOCK || t == DT_WHT);
}

t_dir	*get_stat(t_dir *d, t_args *a, t_options *o, t_max *m)
{
	char *path;
	char *tmp;
	t_dir	*head;

	head = d;
	tmp = ft_strjoin(a->arg, "/");
	init_max(m);
	a->total = 0;
	while (d)
	{
		if (!file_type(d->dirent->d_type))
		{
			d = d->next;
			continue ;
		}
		path = ft_strjoin(tmp, d->dirent->d_name);
		PROTEC(d->fs, ALLOC(t_stat, 1))(NULL);
		if (d->dirent->d_type == DT_LNK)
		{
			if (lstat(path, d->fs) < 0)
				break ;
			d->link_target = ft_strnew(d->fs->st_size + 1);
			if (readlink(path, d->link_target, d->fs->st_size) == -1)
				break ;
		}
		else
		{
			d->link_target = ft_strnew(1);
			if (stat(path, d->fs) < 0)
				break ;
		}
		PROTEC(d->m, ALLOC(t_minmaj, 1))(NULL);
		if (d->dirent->d_type && (d->dirent->d_type == DT_BLK || d->dirent->d_type == DT_CHR))
		{
			d->m->major = major(d->fs->st_rdev);
			d->m->minor = minor(d->fs->st_rdev);
		}
		else
			ft_memdel((void **)&d->m);
		d->p = getpwuid(d->fs->st_uid);
		d->g = getgrgid(d->fs->st_gid);
		if (!hidden(d->dirent->d_name, o))
		{
			set_max(m, d);
			a->total += d->fs->st_blocks;
		}
		ft_memdel((void **)&path);
		d = d->next;
	}
	ft_memdel((void **)&tmp);
	if (!o->f)
	{
		head = sort_content(head);
		if (o->t)
			head = sort_time(head, o);
		if (o->ss)
			head = sort_size(head);
		if (o->r)
			head = rev_content(head);
	}
	return (head);
}
