/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:18:06 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/19 01:49:07 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

static t_args	*sort_args(t_args *a)
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
				flag = 0;
			}
			a = a->next;
		}
		if (flag)
			return (head);
	}
}

t_args			*parse_args(int ac, char **av, int i)
{
	t_args	*head;
	t_args	*cur;

	if (!(head = (t_args *)malloc(sizeof(t_args))))
		return (NULL);
	cur = head;
	cur->arg = ft_strdup(i < ac ? av[i] : ".");
	cur->next = NULL;
	while (++i < ac)
	{
		cur->next = (t_args *)malloc(sizeof(t_args));
		cur = cur->next;
		cur->arg = av[i];
		cur->next = NULL;
	}
	return (sort_args(head));
}
