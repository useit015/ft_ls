/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:26:21 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 21:06:05 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_length;
	size_t	src_length;

	dst_length = 0;
	src_length = ft_strlen(src);
	while (*dst && size > 0)
	{
		dst++;
		dst_length++;
		size--;
	}
	while (*src && size > 1)
	{
		size--;
		*dst++ = *src++;
	}
	if (size == 1 || *src == 0)
		*dst = 0;
	return (src_length + dst_length);
}
