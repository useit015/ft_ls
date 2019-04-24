/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 23:16:39 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/24 05:43:39 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

void	get_min_maj(t_dir *d)
{
	int		type;

	type = d->dirent->d_type ? d->dirent->d_type : 0;
	PROTEC(d->m, ALLOC(t_minmaj, 1));
	if (type == DT_BLK || type == DT_CHR)
	{
		d->m->major = major(d->fs->st_rdev);
		d->m->minor = minor(d->fs->st_rdev);
	}
	else
		ft_memdel((void **)&d->m);
}

int		get_stat(t_dir *d, t_args *a)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(a->arg, "/");
	path = ft_strjoin(tmp, d->dirent->d_name);
	PROTEC(d->fs, ALLOC(t_stat, 1))(0);
	if (d->dirent->d_type == DT_LNK)
	{
		if (lstat(path, d->fs) < 0)
			return (0);
		d->link_target = ft_strnew(d->fs->st_size + 1);
		if (readlink(path, d->link_target, d->fs->st_size) == -1)
			return (0);
	}
	else
	{
		d->link_target = ft_strnew(1);
		if (stat(path, d->fs) < 0)
			return (0);
	}
	ft_memdel((void **)&path);
	ft_memdel((void **)&tmp);
	return (1);
}

t_dir	*sort(t_dir *d, t_o *o)
{
	if (!o->f)
	{
		d = sort_list(d, o, cmp_name);
		if (o->t)
			d = sort_list(d, o, cmp_time);
		if (o->ss)
			d = sort_list(d, o, cmp_size);
		if (o->r)
			d = rev_content(d);
	}
	return (d);
}

t_dir	*prepare_list(t_dir *d, t_args *a, t_o *o, t_max *m)
{
	t_dir	*head;

	head = d;
	init_max(m);
	a->total = 0;
	while (d)
	{
		if (!get_stat(d, a))
			break ;
		get_min_maj(d);
		d->p = getpwuid(d->fs->st_uid);
		d->g = getgrgid(d->fs->st_gid);
		if (!hidden(d->dirent->d_name, o))
		{
			set_max(m, d);
			a->total += d->fs->st_blocks;
		}
		d = d->next;
	}
	return (sort(head, o));
}
