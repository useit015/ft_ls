/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:05:01 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/11 02:38:08 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_options
{
	unsigned int	l:1;
	unsigned int	rr:1;
	unsigned int	a:1;
	unsigned int	r:1;
	unsigned int	t:1;
}					t_options;

typedef struct		s_args
{
	char			*arg;
	struct s_args	*next;
}					t_args;

typedef struct dirent t_dirent;

typedef struct		s_dir
{
	t_dirent		*dirent;
	struct s_dir	*next;
}					t_dir;


#endif
