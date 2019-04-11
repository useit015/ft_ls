/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ujtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 02:10:23 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:54:24 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char		*ft_ujtoa(uintmax_t n)
{
	uintmax_t	tmpn;
	char		*str;
	size_t		len;

	tmpn = n;
	len = 2;
	while (tmpn /= 10)
		len++;
	if ((str = (char*)malloc(sizeof(char) * len)) == 0)
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}
