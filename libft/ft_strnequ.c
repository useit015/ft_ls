/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 05:12:04 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 04:44:27 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!n)
		return (1);
	if (s1 && s2)
	{
		while (s1[i] == s2[i] && s1[i] && i < n - 1)
			i++;
		return (s1[i] == s2[i]);
	}
	return (0);
}
