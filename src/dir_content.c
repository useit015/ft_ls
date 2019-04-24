/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:39:23 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/24 05:13:33 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

void	swap_dir(t_dir *a, t_dir *b)
{
	ft_swap((void *)&a->dirent, (void *)&b->dirent);
	ft_swap((void *)&a->name, (void *)&b->name);
	ft_swap((void *)&a->fs, (void *)&b->fs);
	ft_swap((void *)&a->p, (void *)&b->p);
	ft_swap((void *)&a->g, (void *)&b->g);
	ft_swap((void *)&a->m, (void *)&b->m);
	ft_swap((void *)&a->link_target, (void *)&b->link_target);
}

t_dir	*sort_size(t_dir *d)
{
	t_dir	*head;
	int		flag;

	if (!d)
		return (NULL);
	head = d;
	while (1)
	{
		flag = 1;
		d = head;
		while (d->next)
		{
			if (d->fs->st_size < d->next->fs->st_size)
			{
				swap_dir(d, d->next);
				flag = 0;
			}
			d = d->next;
		}
		if (flag)
			return (head);
	}
}

t_dir	*sort_time(t_dir *d, t_options *o)
{
	t_dir	*head;
	int		flag;

	if (!d)
		return (NULL);
	head = d;
	while (1)
	{
		flag = 1;
		d = head;
		while (d->next)
		{
			if (get_time(d->fs, o) < get_time(d->next->fs, o))
			{
				swap_dir(d, d->next);
				flag = 0;
			}
			d = d->next;
		}
		if (flag)
			return (head);
	}
}

t_dir	*sort_content(t_dir *d)
{
	t_dir	*head;
	int		flag;

	if (!d)
		return (NULL);
	head = d;
	while (1)
	{
		flag = 1;
		d = head;
		while (d->next && d->next->dirent)
		{
			if (ft_strcmp(d->dirent->d_name, d->next->dirent->d_name) > 0)
			{
				swap_dir(d, d->next);
				flag = 0;
			}
			d = d->next;
		}
		if (flag)
			return (head);
	}
}

t_dir	*rev_content(t_dir *d)
{
	t_dir *prev;
	t_dir *next;

	if (!d)
		return (NULL);
	prev = NULL;
	next = NULL;
	while (d)
	{
		next = d->next;
		d->next = prev;
		prev = d;
		d = next;
	}
	return (prev);
}

t_dir	*get_dir_content(t_args *a)
{
	DIR			*dir;
	t_dir		*cur;
	t_dir		*head;
	t_dir		*prev;

	PROTEC(dir, opendir(a->arg))(NULL);
	PROTEC(cur, ALLOC(t_dir, 1))(NULL);
	PROTEC(cur->dirent, ALLOC(t_dirent, 1))(NULL);
	head = cur;
	while (ft_memcpy(cur->dirent, readdir(dir), sizeof(t_dirent)))
	{
		cur->name = cur->dirent->d_name;
		PROTEC(cur->next, ALLOC(t_dir, 1))(NULL);
		prev = cur;
		cur = cur->next;
		PROTEC(cur->dirent, ALLOC(t_dirent, 1))(NULL);
	}
	ft_memdel((void **)&cur->dirent);
	ft_memdel((void **)&cur);
	prev->next = NULL;
	(void)closedir(dir);
	return (head);
}

void	print_rights(t_dir *d)
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

void	print_xattr(t_dir *d, t_args *a, char *base)
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
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		(void)ft_printf("@");
	else
		(void)ft_printf(acl ? "+" : " ");
	ft_memdel((void **)&base);
	ft_memdel((void **)&path);
}

char	*ft_trim(char *s)
{
	int		i;

	while (ft_isspace(*s))
		s++;
	i = ft_strlen(s);
	while (ft_isspace(s[--i]))
		s[i] = 0;
	return (s);
}

char	*format_date(long int t, t_options *o)
{
	char	*s;
	char	*y;
	time_t	now;

	now = time(NULL);
	s = ctime(&t);
	y = ft_trim(ft_strrchr(s, ' '));
	if (o->tt)
		s = ft_strdup(s + 4);
	else if (now - t > SIX_MONTHS || t - now > SIX_MONTHS)
	{
		s[11] = ' ';
		s[12] = 0;
		s = ft_strjoin(s + 4, y);
	}
	else if ((y = ft_strrchr(s, ':')))
	{
		*y = 0;
		s = ft_strdup(s + 4);
	}
	return (s);
}

int		hidden(char *n, t_options *o)
{
	if (!o->a && o->aa && (!ft_strcmp(n, ".") || !ft_strcmp(n, "..")))
		return (1);
	if ((!*n || *n == '.') && !o->a && !o->aa)
		return (1);
	return (0);
}

void	print_long(t_dir *d, t_args *a, t_options *o, t_max *m)
{
	char	*date;

	date = format_date(get_time(d->fs, o), o);
	print_rights(d);
	print_xattr(d, a, ft_strjoin(a->arg, "/"));
	ft_printf("%*d", m->link + 1, d->fs->st_nlink);
	if (!o->g)
		ft_printf(" %-*s ", m->user, d->p->pw_name);
	if (!o->o)
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

void	print_file(t_dir *d, t_args *a, t_options *o, t_max *m)
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

int		is_full(t_dir *d, t_options *o)
{
	while (d && d->name && hidden(d->name, o))
		d = d->next;
	return (d ? 1 : 0);
}

void	print_dir_content(t_dir *d, t_args *a, t_options *o, t_max *m)
{
	if (o->many > 1)
		ft_printf("%s:\n", a->arg);
	if (o->l && is_full(d, o))
		ft_printf("total %d\n", a->total);
	while (d && d->dirent)
	{
		if (!hidden(d->name, o) && d->fs)
			print_file(d, a, o, m);
		d = d->next;
	}
}
