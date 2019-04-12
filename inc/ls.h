/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:43 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/12 03:23:46 by onahiz           ###   ########.fr       */
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

void	ft_swap(void **a, void **b);
void	print_dir_content(t_dir *d, t_args *a, t_options *o, t_max *m);
t_dir	*get_dir_content(char *name);
t_args	*parse_args(int ac, char **av, int i);
int		parse_options(int ac, char **av, t_options *o);

#endif
