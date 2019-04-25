/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 05:49:13 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/24 18:57:23 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

int		cmp_arg_type(t_args *a, t_args *b)
{
	return (is_dir(a->arg) && !is_dir(b->arg));
}

int		cmp_arg_name(t_args *a, t_args *b)
{
	return (ft_strcmp(a->arg, b->arg) > 0);
}

int		cmp_arg_time(t_args *a, t_args *b)
{
	return (a->time < b->time);
}

t_args	*sort_args(t_args *a, int (*cmp)(t_args *, t_args *))
{
	int		flag;
	t_args	*head;

	if (!a)
		return (NULL);
	head = a;
	while (1)
	{
		flag = 1;
		a = head;
		while (a->next)
		{
			if (cmp(a, a->next))
			{
				ft_swap((void *)&a->arg, (void *)&a->next->arg);
				ft_swap((void *)&a->mode, (void *)&a->next->mode);
				ft_swap((void *)&a->time, (void *)&a->next->time);
				flag = 0;
			}
			a = a->next;
		}
		if (flag)
			return (head);
	}
}

t_args	*rev_args(t_args *d)
{
	t_args *prev;
	t_args *next;

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
