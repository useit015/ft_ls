/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:18:06 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/25 01:31:47 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

void			sort_tab(int ac, char **av, int i)
{
	int		j;
	int		flag;

	if (!av || !*av || !ac)
		return ;
	while (1)
	{
		flag = 1;
		j = i;
		while (++j < ac - 1)
		{
			if (ft_strcmp(av[j], av[j + 1]) > 0)
			{
				ft_swap((void *)&av[j], (void *)&av[j + 1]);
				flag = 0;
			}
		}
		if (flag)
			return ;
	}
}

int				arg_err(char **av, int *i)
{
	if (!ft_strlen(av[*i]))
	{
		ft_err("fts_open");
		return (0);
	}
	else
	{
		ft_err(av[(*i)++]);
		return (1);
	}
}

int				check_arg(int ac, char **av, int *i, t_cur *c)
{
	int		f;

	f = 1;
	while (1)
	{
		ft_memdel((void **)&c->s);
		ft_memdel((void **)&c->a->arg);
		c->a->arg = ft_strdup(*i >= ac && f ? "." : av[*i]);
		f = 0;
		PROTEC(c->s, ALLOC(t_stat, 1))(0);
		lstat(c->a->arg, c->s);
		if (!S_ISLNK(c->s->st_mode) && stat(c->a->arg, c->s) < 0)
		{
			if (!arg_err(av, i))
				return (0);
		}
		else
			break ;
		if (*i >= ac)
			break ;
	}
	return (1);
}

t_args			*make_arg(char **av, int ac, t_o *o, int *i)
{
	t_cur	c;

	PROTEC(c.a, ALLOC(t_args, 1))(NULL);
	PROTEC(c.s, ALLOC(t_stat, 1))(NULL);
	c.a->arg = ft_strdup(*i >= ac ? "." : av[*i]);
	if (!check_arg(ac, av, i, &c))
		return (NULL);
	c.a->mode = c.s->st_mode;
	c.a->time = get_time(c.s, o);
	c.a->next = NULL;
	ft_memdel((void **)&c.s);
	return (c.a);
}

t_args			*parse_args(int ac, char **av, int i, t_o *o)
{
	t_args	*head;
	t_args	*cur;

	if (!o->t && !o->f)
		sort_tab(ac, av, i - 1);
	PROTEC(cur, make_arg(av, ac, o, &i))(NULL);
	head = cur;
	while (++i < ac)
	{
		PROTEC(cur->next, make_arg(av, ac, o, &i))(NULL);
		cur = cur->next;
	}
	cur = head;
	if (!o->f)
	{
		head = sort_args(head, cmp_arg_name);
		if (o->t)
			head = sort_args(head, cmp_arg_time);
		if (o->r)
			head = rev_args(head);
	}
	return (sort_args(head, cmp_arg_type));
}
