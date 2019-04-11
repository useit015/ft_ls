/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:03:13 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 02:18:19 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*cpy;

	i = 0;
	if (!s || !f)
		return (NULL);
	if ((cpy = ft_strnew(ft_strlen((char *)s))))
	{
		while (s[i])
		{
			cpy[i] = f(s[i]);
			i++;
		}
		return (cpy);
	}
	return (NULL);
}
