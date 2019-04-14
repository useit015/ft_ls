/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:43 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/14 04:57:39 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include "struct.h"
# include "colors.h"

char	*get_suff(mode_t m);
char	*get_color_start(mode_t m);
char	*get_color_end(mode_t m);
char	get_filetype(mode_t m);
void	ft_swap(void **a, void **b);
void	print_rights(mode_t m);
void	get_stat(t_dir *d, t_args *a, t_options *o, t_max *m);
void	print_dir_content(t_dir *d, t_args *a, t_options *o, t_max *m);
t_dir	*get_dir_content(char *name, t_options *o);
t_args	*parse_args(int ac, char **av, int i);
int		parse_options(int ac, char **av, t_options *o);

#endif
