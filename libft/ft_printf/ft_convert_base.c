/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 04:55:15 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:53:13 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static char	*ft_to_base(unsigned long long nbr, char *base_to, int len)
{
	int		i;
	int		base_l;
	char	*result;

	i = 0;
	base_l = ft_strlen(base_to);
	result = (char *)malloc(sizeof(char) * len);
	if (nbr == 0)
	{
		result[i] = base_to[i];
		i++;
	}
	while (nbr > 0)
	{
		result[i] = base_to[nbr % base_l];
		nbr /= base_l;
		i++;
	}
	result[i] = 0;
	return (result);
}

char		*ft_convert_base(unsigned long long nbr, char *base_to)
{
	unsigned long long	nbr_tmp;
	int					i;
	int					j;
	char				tmp;
	char				*result;

	i = 1;
	nbr_tmp = nbr;
	while (nbr_tmp /= 10)
		i++;
	result = ft_to_base(nbr, base_to, i);
	i = -1;
	j = ft_strlen(result);
	while (++i < --j)
	{
		tmp = result[i];
		result[i] = result[j];
		result[j] = tmp;
	}
	return (result);
}
