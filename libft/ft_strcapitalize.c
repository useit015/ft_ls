/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:13:41 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 21:15:51 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int i;
	int new_word;

	i = 0;
	new_word = 1;
	while (str[i])
	{
		if (ft_isupper(str[i]))
			str[i] += 32;
		if (new_word)
		{
			if (ft_islower(str[i]))
				str[i] -= 32;
			new_word = 0;
		}
		if (str[i] < 48)
			new_word = 1;
		i++;
	}
	return (str);
}
