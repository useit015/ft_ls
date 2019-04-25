/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:05:01 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/25 03:04:28 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct		s_options
{
	unsigned int	l:1;
	unsigned int	t:1;
	unsigned int	c:1;
	unsigned int	d:1;
	unsigned int	p:1;
	unsigned int	g:1;
	unsigned int	o:1;
	unsigned int	a:1;
	unsigned int	aa:1;
	unsigned int	r:1;
	unsigned int	rr:1;
	unsigned int	f:1;
	unsigned int	ff:1;
	unsigned int	u:1;
	unsigned int	uu:1;
	unsigned int	ss:1;
	unsigned int	tt:1;
	unsigned int	many:10;
	char			illegal;
}					t_o;

typedef struct		s_max
{
	unsigned int	link:4;
	unsigned int	user:4;
	unsigned int	group:4;
	unsigned int	maj:4;
	unsigned int	min:4;
	unsigned int	size:8;
}					t_max;

typedef struct		s_args
{
	char			*arg;
	mode_t			mode;
	int				total;
	long			time;
	struct s_args	*next;
}					t_args;

typedef struct		s_minmaj
{
	int				minor;
	int				major;
}					t_minmaj;

typedef struct		s_cur
{
	t_args			*a;
	t_stat			*s;
}					t_cur;

typedef struct		s_dir
{
	char			*name;
	char			*link_target;
	t_minmaj		*m;
	t_dirent		*dirent;
	t_stat			*fs;
	t_passwd		*p;
	t_group			*g;
	struct s_dir	*next;
}					t_dir;

#endif
