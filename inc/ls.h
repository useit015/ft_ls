/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:43 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/26 01:01:29 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <sys/acl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include "colors.h"
# include "struct.h"
# include "../libft/libft.h"
# define SIX_MONTHS 15780000
# define PROTEC(x, y) if (!(x = y)) return
# define ALLOC(type, size) (type *)malloc(sizeof(type) * size)

void	print_file(t_dir *d, t_args *a, t_o *o, t_max *m);
void	print_dir_content(t_dir *d, t_args *a, t_o *o, t_max *m);

t_dir	*prepare_list(t_dir *d, t_args *a, t_o *o, t_max *m);

void	ft_err(char *name);
int		is_dir(char *d);
void	free_dir_content(t_dir *d);

void	init_o(t_o *o);
void	init_max(t_max *m);
void	set_max(t_max *m, t_dir *d);

long	get_time(t_stat *s, t_o *o);
char	*get_suff(mode_t m);
char	*get_color_start(mode_t m);
char	*get_color_end(mode_t m);
char	get_filetype(mode_t m);

void	ft_ls(t_args *a, t_o *o, t_max *m);
void	ft_ls_args(t_args *a, t_o *o, t_max *m);

void	swap_dir(t_dir *a, t_dir *b);
int		is_full(t_dir *d, t_o *o);
int		hidden(char *n, t_o *o);
char	*format_date(long int t, t_o *o);
t_dir	*get_dir_content(t_args *a);

t_dir	*rev_list(t_dir *d);
int		cmp_name(t_dir *a, t_dir *b, t_o *o);
int		cmp_time(t_dir *a, t_dir *b, t_o *o);
int		cmp_size(t_dir *a, t_dir *b, t_o *o);
t_dir	*sort_list(t_dir *d, t_o *o, int(*cmp)(t_dir *, t_dir *, t_o *));

t_args	*rev_args(t_args *d);
int		cmp_arg_type(t_args *a, t_args *b);
int		cmp_arg_time(t_args *a, t_args *b);
int		cmp_arg_name(t_args *a, t_args *b);
t_args	*sort_args(t_args *a, int (*cmp)(t_args *, t_args *));

t_args	*parse_args(int ac, char **av, int i, t_o *o);
int		parse_options(int ac, char **av, t_o *o);

#endif
