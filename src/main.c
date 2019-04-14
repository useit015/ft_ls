/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:49 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/14 04:30:09 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

int		main(int ac, char **av)
{
	int			i;
	t_options	o;
	t_max		m;
	t_args		*a;
	t_dir		*d;

	i = parse_options(ac, av, &o);
	a = parse_args(ac, av, i);
	while (a && a->arg)
	{
		if (o.many > 1)
			ft_printf("%s:\n", a->arg);
		if (!(d = get_dir_content(a->arg, &o)))
			ft_printf("ls: %s: Permission denied\n", ft_strrchr(a->arg, '/') + 1);
		get_stat(d, a, &o, &m);
		print_dir_content(d, a, &o, &m);
		a = a->next;
	}
	return (0);
}
