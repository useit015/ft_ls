/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 05:03:23 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:53:59 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	jtoa_isnegative(intmax_t *n, int *negative)
{
	if (*n < 0)
	{
		*n *= -1;
		*negative = 1;
	}
}

char		*ft_jtoa(intmax_t n)
{
	intmax_t		tmpn;
	int				negative;
	char			*str;
	size_t			len;

	tmpn = n;
	len = 2;
	negative = 0;
	if (n < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	jtoa_isnegative(&n, &negative);
	while (tmpn /= 10)
		len++;
	len += negative;
	if ((str = (char*)malloc(sizeof(char) * len)) == 0)
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	if (negative)
		str[0] = '-';
	return (str);
}
