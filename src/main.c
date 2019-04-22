/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:49 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/22 04:11:29 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

void	free_dir_content(t_dir *d)
{
	t_dir	*t;
	while (d)
	{
		t = d->next;
		ft_memdel((void **)&d->link_target);
		ft_memdel((void **)&d->m);
		ft_memdel((void **)&d->dirent);
		ft_memdel((void **)&d->fs);
		ft_memdel((void **)&d);
		d = t;
	}
}

void	free_args(t_args *a)
{
	t_args	*t;

	while (a)
	{
		t = a->next;
		ft_memdel((void **)&a->arg);
		ft_memdel((void **)&a);
		a = t;
	}
}

int		is_dir(char *d)
{
	DIR			*dir;

	if (!(dir = opendir(d)))
		return (0);
	(void)closedir(dir);
	return (1);
}

void	ft_err(char *name)
{
	write(2, "ls: ", 4);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	perror("");
}

void	recurse(t_dir *d, t_args *a, t_options *o)
{
	t_args	new;
	char	*base;
	t_max	m;

	base = ft_strjoin(a->arg, "/");
	while (d)
	{
		if (S_ISDIR(d->fs->st_mode) && !hidden(d->name, o) && ft_strcmp(d->name, ".") && ft_strcmp(d->name, ".."))
		{
			new.arg = ft_strjoin(base, d->name);
			new.mode = d->fs->st_mode;
			new.time = get_time(d->fs, o);
			ft_printf("\n%s:\n", new.arg);
			ft_ls(&new, o, &m);
		}
		d = d->next;
	}
}

void	ft_ls(t_args *a, t_options *o, t_max *m)
{
	t_dir		*d;
	char		*base;

	if ((S_ISDIR(a->mode) || (!o->l && is_dir(a->arg))) && !o->d)
	{
		if ((d = get_dir_content(a)))
		{
			d = get_stat(d, a, o, m);
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
	else
	{
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
		print_file(d, o, m);
	}
}

void	ft_ls_args(t_args *a, t_options *o, t_max *m)
{
	while (a && a->arg)
	{
		ft_ls(a, o, m);
		if (a->next && a->next->arg && is_dir(a->next->arg) && !o->d)
			ft_printf("\n");
		a = a->next;
	}
}

int		main(int ac, char **av)
{
	int			i;
	t_options	o;
	t_max		m;
	t_args		*a;

	if ((i = parse_options(ac, av, &o)) == -1)
	{
		write(2, "ls: illegal option -- ", 22);
		write(2, &(o.illegal), 1);
		write(2, "\n", 1);
		write(2, "usage: ls [-AFRSUTacdfgloprtu1] [file ...]\n", 43);
		return (1);
	}
	a = parse_args(ac, av, i, &o);
	ft_ls_args(a, &o, &m);
	free_args(a);
	return (0);
}
