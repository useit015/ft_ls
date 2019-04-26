/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:06:00 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/26 01:01:51 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

static void	recurse(t_dir *d, t_args *a, t_o *o)
{
	t_args	new;
	char	*base;
	t_max	m;

	base = ft_strjoin(a->arg, "/");
	while (d)
	{
		if (d->fs && S_ISDIR(d->fs->st_mode) && !hidden(d->name, o)
			&& ft_strcmp(d->name, ".") && ft_strcmp(d->name, ".."))
		{
			new.arg = ft_strjoin(base, d->name);
			new.mode = d->fs->st_mode;
			new.time = get_time(d->fs, o);
			ft_printf("\n%s:\n", new.arg);
			ft_ls(&new, o, &m);
			ft_memdel((void **)&new.arg);
		}
		d = d->next;
	}
	ft_memdel((void **)&base);
}

void		ft_ls_dir(t_args *a, t_o *o, t_max *m)
{
	t_dir	*d;
	char	*base;

	if ((d = get_dir_content(a)))
	{
		d = prepare_list(d, a, o, m);
		print_dir_content(d, a, o, m);
		if (o->rr)
			recurse(d, a, o);
		free_dir_content(d);
	}
	else
	{
		base = ft_strrchr(a->arg, '/');
		ft_err(base ? base + 1 : a->arg);
	}
}

void		ft_ls_file(t_args *a, t_o *o, t_max *m)
{
	t_dir	*d;

	PROTEC(d, ALLOC(t_dir, 1));
	PROTEC(d->fs, ALLOC(t_stat, 1));
	if (lstat(a->arg, d->fs) < 0)
		return ;
	if (!S_ISLNK(d->fs->st_mode))
	{
		if (stat(a->arg, d->fs) < 0)
			return ;
	}
	else
	{
		d->link_target = ft_strnew(d->fs->st_size + 1);
		if (readlink(a->arg, d->link_target, d->fs->st_size) == -1)
			return ;
	}
	d->name = a->arg;
	d->p = getpwuid(d->fs->st_uid);
	d->g = getgrgid(d->fs->st_gid);
	d->m = NULL;
	init_max(m);
	set_max(m, d);
	print_file(d, a, o, m);
}

void		ft_ls(t_args *a, t_o *o, t_max *m)
{
	if ((S_ISDIR(a->mode) || (!o->l && is_dir(a->arg))) && !o->d)
		ft_ls_dir(a, o, m);
	else
		ft_ls_file(a, o, m);
}

void		ft_ls_args(t_args *a, t_o *o, t_max *m)
{
	while (a && a->arg)
	{
		ft_ls(a, o, m);
		if (a->next && a->next->arg && is_dir(a->next->arg) && !o->d)
			ft_printf("\n");
		a = a->next;
	}
}
