/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:05:01 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/20 02:10:23 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct dirent t_dirent;
typedef struct stat t_stat;
typedef struct passwd t_passwd;
typedef struct group t_group;

typedef struct		s_options
{
	unsigned int	l:1;
	unsigned int	t:1;
	unsigned int	g:1;
	unsigned int	a:1;
	unsigned int	aa:1;
	unsigned int	r:1;
	unsigned int	rr:1;
	unsigned int	f:1;
	unsigned int	ff:1;
	unsigned int	many:20;
}					t_options;

typedef struct		s_max
{
	unsigned int	link:4;
	unsigned int	user:4;
	unsigned int	group:4;
	unsigned int	major:4;
	unsigned int	minor:4;
	unsigned int	size:8;
	unsigned int	total;
}					t_max;

typedef struct		s_args
{
	char			*arg;
	int				total;
	struct s_args	*next;
}					t_args;

typedef struct		s_minmaj
{
	int				minor;
	int				major;
}					t_minmaj;

typedef struct		s_dir
{
	char			*link_target;
	t_minmaj		*m;
	t_dirent		*dirent;
	t_stat			*fs;
	t_passwd		*p;
	t_group			*g;
	struct s_dir	*next;
}					t_dir;

#endif
