/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:39:23 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/12 04:25:16 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

void		ft_swap(void **a, void **b)
{
	void *t = *a;
	*a = *b;
	*b = t;
}

static t_dir	*sort_content(t_dir *d)
{
	if (!d)
			return (NULL);
	t_dir *head = d;
	while (1)
	{
		int flag = 1;
		d = head;
		while (d->next && d->next->dirent)
		{
			if (ft_strcmp(d->dirent->d_name, d->next->dirent->d_name) > 0)
			{
				ft_swap((void *)&d->dirent, (void *)&d->next->dirent);
				flag = 0;
			}
			d = d->next;
		}
		if (flag)
				return (head);
	}
}

t_dir		*get_dir_content(char *name)
{
	DIR			*dir;
	t_dir		*cur;
	t_dir		*head;

	if (!(dir = opendir(name)))
		ft_printf("i can't read this shit --> |%s|\n", name);
	cur = (t_dir *)malloc(sizeof(t_dir));
	head = cur;
	cur->next = NULL;
	while ((cur->dirent = readdir(dir)) != NULL)
	{
		cur->next = (t_dir *)malloc(sizeof(t_dir));
		cur = cur->next;
	}
	closedir(dir);
	return (sort_content(head));
}

static void	print_rights(mode_t m)
{
	ft_printf(S_ISDIR(m) ? "d" : S_ISLNK(m) ? "l" : "-");
	ft_printf(m & S_IRUSR ? "r" : "-");
	ft_printf(m & S_IWUSR ? "w" : "-");
	ft_printf(m & S_IXUSR ? "x" : "-");
	ft_printf(m & S_IRGRP ? "r" : "-");
	ft_printf(m & S_IWGRP ? "w" : "-");
	ft_printf(m & S_IXGRP ? "x" : "-");
	ft_printf(m & S_IROTH ? "r" : "-");
	ft_printf(m & S_IWOTH ? "w" : "-");
	ft_printf(m & S_IXOTH ? "x" : "-");
}

char		*trim_date(char *s)
{
	int		i;

	i = ft_strlen(s);
	while (s[--i] != ':')
		;
	if (s[i] == ':')
		s[i] = 0;
	return (s + 4);
}

void		print_dir_content(t_dir *d, t_args *a, t_options *o, t_max *m)
{
	if (o->many > 1)
		ft_printf("%s:\n", a->arg);
	while (d && d->dirent)
	{
		while (*d->dirent->d_name == '.' && !o->a)
			d = d->next;
		char *s = d->dirent->d_type == DT_DIR ? CYAN : d->dirent->d_type == DT_LNK ? MAGENTA : d->fs->st_mode & S_IXUSR ? RED : "";
		char *e = d->dirent->d_type == 4 || d->dirent->d_type == 10 || d->fs->st_mode & S_IXUSR ? EOC : "";
		if (o->l)
		{
			print_rights(d->fs->st_mode);
			ft_printf("%*d", m->link + 2, d->fs->st_nlink);
			ft_printf("%*s", m->user + 1, d->p->pw_name);
			ft_printf("%*s", m->group + 2, d->g->gr_name);
			ft_printf("%*lld", m->size + 2, d->fs->st_size);
			ft_printf(" %s ", trim_date(ctime(&d->fs->st_mtimespec.tv_sec)));
		}
		ft_printf("%s%s%s", s, d->dirent->d_name, e);
		if (o->l && d->dirent->d_type == DT_LNK)
			ft_printf(" -> %s", d->link_target);
		ft_printf("\n");
		d = d->next;
	}
	if (a->next && a->next->arg)
		ft_printf("\n");
}
