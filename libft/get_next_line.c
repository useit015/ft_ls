/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 01:44:43 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/10 23:24:30 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_linelen(char *tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i] != 10 && tab[i])
		i++;
	return (i);
}

static char			*ft_line(char *tab)
{
	if (ft_strchr(tab, 10))
	{
		ft_strcpy(tab, ft_strchr(tab, 10) + 1);
		return (tab);
	}
	if (ft_linelen(tab) > 0)
	{
		ft_strcpy(tab, ft_strchr(tab, 0));
		return (tab);
	}
	return (NULL);
}

int					get_next_line(int const fd, char **line)
{
	char			*tmp;
	char			buff[BUFF_SIZE + 1];
	static	char	*tab[256];
	int				ret;

	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!(tab[fd]) && (tab[fd] = ft_strnew(0)) == NULL)
		return (-1);
	while (!(ft_strchr(tab[fd], 10)) && (ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = 0;
		tmp = tab[fd];
		tab[fd] = ft_strnjoin(tmp, buff, ret);
		free(tmp);
	}
	*line = ft_strsub(tab[fd], 0, ft_linelen(tab[fd]));
	return (ft_line(tab[fd]) != NULL);
}
