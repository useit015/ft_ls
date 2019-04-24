/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:18:06 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/24 05:58:25 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

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

t_args			*make_arg(char **av, int ac, t_o *o, int *i)
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

t_args			*parse_args(int ac, char **av, int i, t_o *o)
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
		head = sort_args(head, cmp_arg_name);
		if (o->t)
			head = sort_args(head, cmp_arg_time);
		if (o->r)
			head = rev_args(head);
	}
	return (sort_args(head, cmp_arg_type));
}
