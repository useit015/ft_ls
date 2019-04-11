/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:29:50 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 21:45:23 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_result(unsigned long long result, int sign, const char *str)
{
	size_t count;

	count = 0;
	while (*str <= '1' || *str >= '9')
		str++;
	while (ft_isdigit(*(str + count)))
		count++;
	if (result > 9223372036854775807 || count >= 19)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	else
		return (result * sign);
}

int			ft_atoi(const char *str)
{
	unsigned long long	result;
	size_t				i;
	size_t				length;
	int					sign;

	i = 0;
	sign = 1;
	result = 0;
	length = ft_strlen((char *)str);
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (i <= length)
	{
		if (ft_isdigit(str[i]))
			result = (result * 10) + (str[i] - 48);
		else
			return (get_result(result, sign, str));
		i++;
	}
	return (get_result(result, sign, str));
}
