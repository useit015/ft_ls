/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:18:06 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/24 03:02:21 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

t_args			*rev_args(t_args *d)
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

t_args			*sort_types(t_args *a)
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
			if (is_dir(a->arg) && !is_dir(a->next->arg))
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

t_args			*sort_args_time(t_args *a)
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
			if (a->time < a->next->time)
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

t_args			*sort_args(t_args *a)
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
		while (a->next && a->next->arg)
		{
			if (ft_strcmp(a->arg, a->next->arg) > 0)
			{
				ft_swap((void *)&a->arg, (void *)&a->next->arg);
				ft_swap((void *)&a->mode, (void *)&a->next->mode);
				flag = 0;
			}
			a = a->next;
		}
		if (flag)
			return (head);
	}
}

void			sort_tab(int ac, char **av, int i)
{
	int		flag;

	if (!av || !*av || !ac)
		return ;
	while (1)
	{
		flag = 1;
		while (++i < ac - 1)
		{
			if (ft_strcmp(av[i], av[i + 1]) > 0)
			{
				ft_swap((void *)&av[i], (void *)&av[i + 1]);
				flag = 0;
			}
		}
		if (flag)
			return ;
	}
}

t_args			*make_arg(char **av, int ac, t_options *o, int *i)
{
	t_args	*cur;
	t_stat	s;
	int		f;

	f = 1;
	PROTEC(cur, ALLOC(t_args, 1))(NULL);
	cur->arg = ft_strdup(*i >= ac && f ? "." : av[*i]);
	while (1)
	{
		free(cur->arg);
		cur->arg = ft_strdup(*i >= ac && f ? "." : av[*i]);
		f = 0;
		lstat(cur->arg, &s);
		if (!S_ISLNK(s.st_mode) && stat(cur->arg, &s) < 0)
			ft_err(av[(*i)++]);
		else
			break ;
		if (*i >= ac)
			break ;
	}
	cur->mode = s.st_mode;
	cur->time = get_time(&s, o);
	cur->next = NULL;
	return (cur);
}

t_args			*parse_args(int ac, char **av, int i, t_options *o)
{
	t_args	*head;
	t_args	*cur;

	if (!o->t && !o->f)
		sort_tab(ac, av, i - 1);
	cur = make_arg(av, ac, o, &i);
	head = cur;
	while (++i < ac)
	{
		cur->next = make_arg(av, ac, o, &i);
		cur = cur->next;
	}
	cur = head;
	if (!o->f)
	{
		head = sort_args(head);
		if (o->t)
			head = sort_args_time(head);
		if (o->r)
			head = rev_args(head);
	}
	return (sort_types(head));
}
