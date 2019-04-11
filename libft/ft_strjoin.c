/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 18:52:09 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/15 23:05:29 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	t_length;

	if (!s1 || !s2)
		return (NULL);
	t_length = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	if (!(result = (char *)malloc(sizeof(char) * t_length)))
		return (NULL);
	return (ft_strcat(ft_strcpy(result, (char *)s1), (char *)s2));
}
