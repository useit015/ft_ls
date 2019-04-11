/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoea.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 03:52:53 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:53:35 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static char	*get_suffix(char c, int i, int j)
{
	char	*suff;

	suff = ft_strnew(10);
	suff[0] = c;
	if (i)
		suff[1] = '-';
	else
	{
		suff[1] = '+';
		i = j;
	}
	if (i >= 0 && i < 10)
		suff = ft_strcat(ft_strcat(suff, "0"), ft_itoa(i));
	else
		suff = ft_strcat(suff, ft_itoa(i));
	return (suff);
}

static char	*ft_ftoea_null(int p, char c)
{
	if (c == 'e')
		return (ft_strjoin(ft_ftoa(0, p), "e+00"));
	else
		return (ft_strjoin(ft_ftoa(0, p), "E+00"));
}

static void	free_buffs(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

char		*ft_ftoea(double f, int p, char c)
{
	int		i;
	int		j;
	char	*s;
	char	*tmp;
	char	*suff;

	i = 0;
	j = 0;
	if (!f)
		return (ft_ftoea_null(p, c));
	while (f < 1)
	{
		f *= 10;
		i++;
	}
	while (!i && f >= 10)
	{
		f /= 10;
		j++;
	}
	tmp = ft_ftoa(f, p);
	suff = get_suffix(c, i, j);
	s = ft_strjoin(tmp, suff);
	free_buffs(suff, tmp);
	return (s);
}
