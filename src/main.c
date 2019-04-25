/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:49 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/25 01:31:20 by onahiz           ###   ########.fr       */
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

int		is_dir(char *d)
{
	DIR			*dir;

	if (!(dir = opendir(d)))
		return (0);
	(void)closedir(dir);
	return (1);
}

void	ft_err(char *name)
{
	write(2, "ls: ", 4);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	perror("");
}

int		main(int ac, char **av)
{
	int			i;
	t_o			o;
	t_max		m;
	t_args		*a;

	if ((i = parse_options(ac, av, &o)) == -1)
	{
		write(2, "ls: illegal option -- ", 22);
		write(2, &(o.illegal), 1);
		write(2, "\n", 1);
		write(2, "usage: ls [-AFRSUTacdfgloprtu1] [file ...]\n", 43);
		return (1);
	}
	PROTEC(a, parse_args(ac, av, i, &o))(1);
	ft_ls_args(a, &o, &m);
	free_args(a);
	return (0);
}
