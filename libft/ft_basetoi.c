/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basetoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:13:55 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/22 04:15:37 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_get_val(char c, char *base)
{
	int i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	ft_basetoi(char *str, char *base_from)
{
	int i;
	int nb;
	int power;
	int	base_len;

	nb = 0;
	power = 1;
	base_len = ft_strlen(base_from);
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (ft_get_val(str[i], base_from) < 0)
			return (0);
		nb += ft_get_val(str[i], base_from) * power;
		power *= base_len;
		i--;
	}
	return (nb);
}
