/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 02:21:20 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/19 02:22:09 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;

	if (!(dest = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	dest = ft_strncpy(dest, (char *)src, n);
	dest[n] = 0;
	return (dest);
}
