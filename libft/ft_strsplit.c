/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 05:13:04 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 02:21:25 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_delimiter(char c, char d)
{
	return (c == d);
}

static int		count_dels(char *str, char d)
{
	size_t spaces;

	spaces = 0;
	while (*str)
	{
		if (is_delimiter(*str, d) && !is_delimiter(*(str + 1), d))
			spaces++;
		str++;
	}
	return (spaces);
}

static int		chars_in_word(char *str, char d)
{
	size_t chars;

	chars = 0;
	while (*str)
	{
		if (!is_delimiter(*str, d))
			chars++;
		else
			break ;
		str++;
	}
	return (chars);
}

static char		*make_word(char *str, size_t *index, char d)
{
	char	*word;
	size_t	i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (chars_in_word(str + *index, d) + 1));
	while (!is_delimiter(str[*index], d) && str[*index])
	{
		word[i] = str[*index];
		(*index)++;
		i++;
	}
	word[i] = 0;
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	*str;
	char	**strv;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	if (!(str = (char *)s))
		return (NULL);
	if (!(strv = (char **)malloc(sizeof(char *) * (count_dels(str, c) + 2))))
		return (NULL);
	while (str[i])
	{
		if (is_delimiter(str[i], c))
			i++;
		else
		{
			strv[j] = make_word(str, &i, c);
			j++;
		}
	}
	strv[j] = NULL;
	return (strv);
}
