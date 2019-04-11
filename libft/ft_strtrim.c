/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 21:32:54 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 02:21:25 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_ws(char c)
{
	return (c == '\n' || c == '\t' || c == ' ');
}

char		*ft_strtrim(char const *s)
{
	char	*result;
	char	*cs;
	size_t	j;

	if (!s)
		return (NULL);
	cs = (char *)s;
	while (*cs && is_ws(*cs))
		cs++;
	j = ft_strlen(cs);
	while (is_ws(cs[j - 1]) && j > 0)
		j--;
	if (!(result = (char *)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	result = ft_strncpy(result, cs, j);
	result[j] = '\0';
	return (result);
}
