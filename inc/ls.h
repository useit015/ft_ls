/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:43 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/24 05:22:30 by onahiz           ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include "colors.h"
# include "struct.h"
# include "../libft/libft.h"
# define SIX_MONTHS 15780000
# define ALLOC(type, size) (type *)malloc(sizeof(type) * size)
# define PROTEC(x, y) if (!(x = y)) return

void	init_options(t_options *o);
void	set_max(t_max *m, t_dir *d);
void	free_dir_content(t_dir *d);
void	ft_ls_args(t_args *a, t_options *o, t_max *m);
void	print_file(t_dir *d, t_args *a, t_options *o, t_max *m);
void	init_max(t_max *m);
int		is_dir(char *d);
void	ft_err(char *name);
void	set_max(t_max *m, t_dir *d);
t_dir	*sort_content(t_dir *d);
t_dir	*rev_content(t_dir *d);
t_dir	*sort_time(t_dir *d, t_options *o);
t_dir	*sort_size(t_dir *d);
void	check_d(char *n, t_dir *d);
int		hidden(char *n, t_options *o);
long	get_time(t_stat *s, t_options *o);
char	*get_suff(mode_t m);
char	*get_color_start(mode_t m);
char	*get_color_end(mode_t m);
char	get_filetype(mode_t m);
void	ft_swap(void **a, void **b);
void	ft_ls(t_args *a, t_options *o, t_max *m);
t_dir	*prepare_list(t_dir *d, t_args *a, t_options *o, t_max *m);
void	print_dir_content(t_dir *d, t_args *a, t_options *o, t_max *m);
t_dir	*get_dir_content(t_args *a);
t_args	*parse_args(int ac, char **av, int i, t_options *o);
int		parse_options(int ac, char **av, t_options *o);

#endif
