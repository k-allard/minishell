/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:14:34 by kallard           #+#    #+#             */
/*   Updated: 2020/05/19 00:39:39 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Iterates the list lst and applies f() to the content of each element.
** Copies lst to a new list dynamically allocated.
** Del() deletes the content of an element if needed.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newhead;

	if (!lst)
		return (NULL);
	if (!(newlist = ft_lstnew(f(lst->content))))
		return (NULL);
	newhead = newlist;
	while (lst)
	{
		if (lst->next)
		{
			if (!(newlist->next = ft_lstnew(f(lst->next->content))))
			{
				ft_lstclear(&newhead, del);
				return (NULL);
			}
			newlist = newlist->next;
		}
		lst = lst->next;
	}
	newlist->next = NULL;
	return (newhead);
}
