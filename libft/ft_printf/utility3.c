/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 07:58:19 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:44:15 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle.h"

char	*new_fspec(t_param *arg, char f)
{
	char	*s;

	s = ft_strnew(2);
	*s = f;
	arg->f = 'c';
	return (s);
}

int		is_fspec(char f)
{
	if (ft_strchr("%cCsSdDiuUxXoOpbfFeE", f))
		return (1);
	return (0);
}

int		is_flag(char f)
{
	if (ft_strchr(" +-.#lhjzL$'*", f) || ft_isdigit(f))
		return (1);
	return (0);
}

int		get_next_spec(char *f)
{
	int		i;

	i = -1;
	while (f[++i])
	{
		if (f[i] == '%')
			return (i);
	}
	return (i);
}

char	*skip_flags(char *f)
{
	while (*f && is_flag(*f))
		f++;
	return (f);
}
