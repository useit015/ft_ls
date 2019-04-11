/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:39:23 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/11 04:20:24 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

static void		ft_swap_dirent(t_dirent **a, t_dirent **b)
{
	t_dirent *t = *a;
	*a = *b;
	*b = t;
}

static t_dir	*sort_content(t_dir *d)
{
	if (!d)
			return (NULL);
	t_dir *head = d;
	while (1)
	{
		int flag = 1;
		d = head;
		while (d->next && d->next->dirent)
		{
			if (ft_strcmp(d->dirent->d_name, d->next->dirent->d_name) > 0)
			{
				ft_swap_dirent(&d->dirent, &d->next->dirent);
				flag = 0;
			}
			d = d->next;
		}
		if (flag)
				return (head);
	}
}

t_dir	*get_dir_content(char *name)
{
	DIR			*dir;
	t_dir		*cur;
	t_dir		*head;

	if (!(dir = opendir(name)))
		ft_printf("i can't read this shit --> |%s|\n", name);
	cur = (t_dir *)malloc(sizeof(t_dir));
	head = cur;
	cur->next = NULL;
	while ((cur->dirent = readdir(dir)) != NULL)
	{
		cur->next = (t_dir *)malloc(sizeof(t_dir));
		cur = cur->next;
	}
	closedir(dir);
	return (sort_content(head));
}

void	print_dir_content(t_dir *d, t_args *a, int many)
{
	if (many > 1)
		ft_printf("%s:\n", a->arg);
	while (d && d->dirent)
	{
		while (*d->dirent->d_name == '.')
			d = d->next;
		char *s = d->dirent->d_type == DT_DIR ? CYAN : d->dirent->d_type == DT_LNK ? MAGENTA : "";
		char *e = d->dirent->d_type == 4 || d->dirent->d_type == 10 ? EOC : "";
		ft_printf("%s%s%s\n", s, d->dirent->d_name, e);
		d = d->next;
	}
	if (a->next && a->next->arg)
		ft_printf("\n");
}
