/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:39:23 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/24 05:47:07 by onahiz           ###   ########.fr       */
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

char	*format_date(long int t, t_o *o)
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

int		hidden(char *n, t_o *o)
{
	if (!o->a && o->aa && (!ft_strcmp(n, ".") || !ft_strcmp(n, "..")))
		return (1);
	if ((!*n || *n == '.') && !o->a && !o->aa)
		return (1);
	return (0);
}

int		is_full(t_dir *d, t_o *o)
{
	while (d && d->name && hidden(d->name, o))
		d = d->next;
	return (d ? 1 : 0);
}
