/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 05:40:25 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/26 00:41:27 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

static void	print_rights(t_dir *d)
{
	mode_t		m;

	m = d->fs->st_mode;
	(void)ft_printf("%c", get_filetype(m));
	(void)ft_printf(m & S_IRUSR ? "r" : "-");
	(void)ft_printf(m & S_IWUSR ? "w" : "-");
	if (m & S_ISUID)
		(void)ft_printf(m & S_IXUSR ? "s" : "S");
	else
		(void)ft_printf(m & S_IXUSR ? "x" : "-");
	(void)ft_printf(m & S_IRGRP ? "r" : "-");
	(void)ft_printf(m & S_IWGRP ? "w" : "-");
	if (m & S_ISGID)
		(void)ft_printf(m & S_IXGRP ? "s" : "S");
	else
		(void)ft_printf(m & S_IXGRP ? "x" : "-");
	(void)ft_printf(m & S_IROTH ? "r" : "-");
	(void)ft_printf(m & S_IWOTH ? "w" : "-");
	if (m & S_ISVTX)
		(void)ft_printf(m & S_IXOTH ? "t" : "T");
	else
		(void)ft_printf(m & S_IXOTH ? "x" : "-");
}

static void	print_xattr(t_dir *d, t_args *a, char *base)
{
	acl_t		acl;
	acl_entry_t	tmp;
	ssize_t		xattr;
	char		*path;

	xattr = 0;
	acl = NULL;
	if (ft_strcmp(a->arg, d->name))
		path = ft_strjoin(base, d->name);
	else
		path = ft_strdup(d->name);
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &tmp) == -1)
		acl = NULL;
	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		(void)ft_printf("@");
	else
		(void)ft_printf(acl ? "+" : " ");
	acl_free(acl);
	ft_memdel((void **)&base);
	ft_memdel((void **)&path);
}

static void	print_long(t_dir *d, t_args *a, t_o *o, t_max *m)
{
	char	*date;

	date = format_date(get_time(d->fs, o), o);
	print_rights(d);
	print_xattr(d, a, ft_strjoin(a->arg, "/"));
	ft_printf("%*d", m->link + 1, d->fs->st_nlink);
	if (!o->g && d->p)
		ft_printf(" %-*s ", m->user, d->p->pw_name);
	if (!o->o && d->g)
		ft_printf(" %-*s ", m->group, d->g->gr_name);
	if (o->g && o->o)
		ft_printf("  ");
	if (S_ISBLK(d->fs->st_mode) || S_ISCHR(d->fs->st_mode))
		ft_printf("%*d, %*d", m->maj + 2, d->m->major, m->min, d->m->minor);
	else
		ft_printf("%*lld", m->size + 1, d->fs->st_size);
	ft_printf(" %s ", date);
	free(date);
}

void		print_file(t_dir *d, t_args *a, t_o *o, t_max *m)
{
	if (o->l)
		print_long(d, a, o, m);
	// ft_printf(get_color_start(d->fs->st_mode));
	ft_printf(d->name);
	// ft_printf(get_color_end(d->fs->st_mode));
	if (o->ff)
		ft_printf("%s", get_suff(d->fs->st_mode));
	else if (o->p && S_ISDIR(d->fs->st_mode))
		ft_printf("/");
	if (o->l && S_ISLNK(d->fs->st_mode))
		ft_printf(" -> %s", d->link_target);
	ft_printf("\n");
}

void		print_dir_content(t_dir *d, t_args *a, t_o *o, t_max *m)
{
	if (o->many > 1)
		ft_printf("%s:\n", a->arg);
	if (o->l && is_full(d, o))
		ft_printf("total %d\n", a->total);
	while (d && d->dirent)
	{
		if (!hidden(d->name, o) && d->fs && d->fs->st_mode)
			print_file(d, a, o, m);
		d = d->next;
	}
}
