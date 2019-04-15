/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 23:16:39 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/15 04:27:38 by onahiz           ###   ########.fr       */
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

void	set_max(t_max *m, t_dir *d)
{
	m->link = max(ft_intlen(d->fs->st_nlink), m->link);
	m->user = max(ft_strlen(d->p->pw_name), m->user);
	m->group = max(ft_strlen(d->g->gr_name), m->group);
	m->size = max(ft_intlen(d->fs->st_size), m->size);
	m->major = max(ft_intlen(d->m.major), m->major);
}

void	check_d(char *n, t_dir *d)
{
	t_stat s;
	while (d && d->dirent)
	{
		if (d->dirent->d_type == DT_BLK || d->dirent->d_type == DT_CHR)
		{
			if (stat(ft_strjoin(n, d->dirent->d_name), &s) < 0)
					break ;
			ft_printf("i am in files |%29s| --> |%d|", d->dirent->d_name, s.st_rdev);
			ft_printf(">> minor >> |%d| >> major >> |%d|\n", minor(s.st_rdev), major(s.st_rdev));
		}
		d = d->next;
	}
}

int		file_type(int t)
{
	return (t == DT_FIFO || t == DT_CHR || t == DT_BLK || t == DT_REG || t == DT_DIR || t == DT_LNK || t == DT_SOCK || t == DT_WHT);
}

void	set_ids(t_stat *s, t_passwd **p, t_group **g)
{
	*p = getpwuid(s->st_uid);
	*g = getgrgid(s->st_gid);
}

void	get_stat(t_dir *d, t_args *a, t_options *o, t_max *m)
{
	char *path;
	char *tmp;

	tmp = ft_strjoin(a->arg, "/");
	init_max(m);
	a->total = 0;
	while (d && d->dirent)
	{
		if (!file_type(d->dirent->d_type))
		{
			d = d->next;
			continue ;
		}
		path = ft_strjoin(tmp, d->dirent->d_name);
		d->fs = (t_stat *)malloc(sizeof(t_stat));
		if (d->dirent->d_type == DT_LNK)
		{
			if (lstat(path, d->fs) < 0)
				break ;
			d->link_target = (char *)malloc(sizeof(char) * (d->fs->st_size + 1));
			if (readlink(path, d->link_target, d->fs->st_size) == -1)
				break ;
		}
		else if (stat(path, d->fs) < 0)
			break ;
		if (d->dirent->d_type && (d->dirent->d_type == DT_BLK || d->dirent->d_type == DT_CHR))
		{
			d->m.major = major(d->fs->st_rdev);
			d->m.minor = minor(d->fs->st_rdev);
		}
		set_ids(d->fs, &d->p, &d->g);
		if (!hidden(d->dirent->d_name, o))
		{
			set_max(m, d);
			a->total += d->fs->st_blocks;
		}
		free(path);
		d = d->next;
	}
	free(tmp);
}
