/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 20:54:10 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 02:29:06 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *cur;

	if (alst && del)
	{
		while (*alst)
		{
			cur = *alst;
			del(cur->content, cur->content_size);
			*alst = (*alst)->next;
			free(cur);
			cur = NULL;
		}
	}
}
