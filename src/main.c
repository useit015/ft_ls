/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:49 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/20 03:30:12 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

void	free_dir_content(t_dir *d)
{
	t_dir	*t;
	while (d)
	{
		t = d->next;
		ft_memdel((void **)&d->link_target);
		ft_memdel((void **)&d->m);
		ft_memdel((void **)&d->dirent);
		ft_memdel((void **)&d->fs);
		ft_memdel((void **)&d);
		d = t;
	}
}

void	free_args(t_args *a)
{
	t_args	*t;

	while (a)
	{
		t = a->next;
		ft_memdel((void **)&a->arg);
		ft_memdel((void **)&a);
		a = t;
	}
}

int		main(int ac, char **av)
{
	int			i;
	t_options	o;
	t_max		m;
	t_args		*a;
	t_dir		*d;
	t_args		*at;

	i = parse_options(ac, av, &o);
	a = parse_args(ac, av, i);
	at = a;
	while (a && a->arg)
	{
		if (o.many > 1)
			ft_printf("%s:\n", a->arg);
		if ((d = get_dir_content(a)))
		{
			d = get_stat(d, a, &o, &m);
			print_dir_content(d, a, &o, &m);
			free_dir_content(d);
		}
		else
		{
			char *base = ft_strrchr(a->arg, '/');
			base = base ? base + 1 : a->arg;
			write(2, "ls: ", 4);
			write(2, base, ft_strlen(base));
			write(2, ": ", 2);
			perror("");
		}
		a = a->next;
	}
	free_args(at);
	return (0);
}
