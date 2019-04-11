/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:49 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/11 04:19:45 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

int		main(int ac, char **av)
{
	int			i;
	t_options	o;
	t_args		*a;
	t_dir		*d;

	i = parse_options(ac, av, &o);
	a = parse_args(ac, av, i);
	while (a && a->arg)
	{
		d = get_dir_content(a->arg);
		print_dir_content(d, a, ac - i);
		a = a->next;
	}
	return (0);
}
