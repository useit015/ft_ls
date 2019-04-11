/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 05:00:20 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 02:18:19 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	length;

	length = ft_strlen((char *)src) + 1;
	dest = (char *)malloc(sizeof(char) * length);
	if (dest)
		return (ft_strcpy(dest, (char *)src));
	return (0);
}
