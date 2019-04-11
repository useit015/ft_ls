/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:42:34 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 02:21:25 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t i;

	if (!*n)
		return ((char *)h);
	while (*h && len > 0)
	{
		i = 0;
		while (h[i] == n[i] && n[i] && i - len > 0)
			i++;
		if (!n[i])
			return ((char *)h);
		h++;
		len--;
	}
	return (0);
}
