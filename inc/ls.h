/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:22:43 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/11 04:20:30 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <dirent.h>
# include "../libft/libft.h"
# include "struct.h"
# include "colors.h"

void	print_dir_content(t_dir *d, t_args *a, int many);
t_dir	*get_dir_content(char *name);
t_args	*parse_args(int ac, char **av, int i);
int		parse_options(int ac, char **av, t_options *o);

#endif
