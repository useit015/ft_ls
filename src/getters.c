/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 04:55:22 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/23 01:10:40 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ls.h"

char	get_filetype(mode_t m)
{
	if (S_ISDIR(m))
		return ('d');
	else if (S_ISLNK(m))
		return ('l');
	else if (S_ISFIFO(m))
		return ('p');
	else if (S_ISSOCK(m))
		return ('s');
	else if (S_ISBLK(m))
		return ('b');
	else if (S_ISCHR(m))
		return ('c');
	else
		return ('-');
}

char	*get_color_start(mode_t m)
{
	if (S_ISDIR(m))
		return (CYAN);
	else if (S_ISLNK(m))
		return (MAGENTA);
	else if (m & S_IXUSR)
		return (RED);
	else if (S_ISFIFO(m))
		return (YELLOW);
	else if (S_ISSOCK(m))
		return (GREEN);
	else if (S_ISBLK(m))
		return (BG_CYAN);
	else if (S_ISCHR(m))
		return (BG_YELLOW);
	else
		return ("");
}

char	*get_color_end(mode_t m)
{
	if (S_ISDIR(m) || S_ISLNK(m) || m & S_IXUSR || S_ISFIFO(m)
		|| S_ISBLK(m) || S_ISCHR(m) || S_ISSOCK(m))
		return (EOC);
	else
		return ("");
}

char	*get_suff(mode_t m)
{
	if (S_ISDIR(m))
		return ("/");
	else if (S_ISLNK(m))
		return ("@");
	else if (S_ISFIFO(m))
		return ("|");
	else if (S_ISSOCK(m))
		return ("=");
	else if (m & (S_IXUSR | S_IXGRP | S_IXOTH))
		return ("*");
	else
		return ("");
}

long	get_time(t_stat *s, t_options *o)
{
	if (o->u)
		return (s->st_atimespec.tv_sec);
	else if (o->c)
		return (s->st_ctimespec.tv_sec);
	else if (o->uu)
		return (s->st_birthtimespec.tv_sec);
	else
		return (s->st_mtimespec.tv_sec);
}
