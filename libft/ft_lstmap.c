/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 22:03:43 by onahiz            #+#    #+#             */
/*   Updated: 2018/10/11 21:48:40 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*cur;
	t_list	*temp;
	t_list	*head;

	if (!lst || !f)
		return (NULL);
	temp = f(lst);
	if (!(cur = ft_lstnew(temp->content, temp->content_size)))
		return (NULL);
	head = cur;
	lst = lst->next;
	while (lst)
	{
		temp = f(lst);
		if (!(cur->next = ft_lstnew(temp->content, temp->content_size)))
			return (NULL);
		cur = cur->next;
		lst = lst->next;
	}
	return (head);
}
