/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 05:39:22 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/24 18:59:08 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

int		cmp_size(t_dir *a, t_dir *b, t_o *o)
{
	o = NULL;
	return (a->fs->st_size < b->fs->st_size);
}

int		cmp_name(t_dir *a, t_dir *b, t_o *o)
{
	o = NULL;
	return (ft_strcmp(a->dirent->d_name, b->dirent->d_name) > 0);
}

int		cmp_time(t_dir *a, t_dir *b, t_o *o)
{
	return (get_time(a->fs, o) < get_time(b->fs, o));
}

t_dir	*sort_list(t_dir *d, t_o *o, int (*cmp)(t_dir *, t_dir *, t_o *))
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
			if (cmp(d, d->next, o))
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

t_dir	*rev_list(t_dir *d)
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
