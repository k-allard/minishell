/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:12:07 by kallard           #+#    #+#             */
/*   Updated: 2020/05/18 23:43:49 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Deletes with del() and frees the element *lst and it's every successor.
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*arch_elem;

	if (!del || !*lst)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		arch_elem = *lst;
		*lst = arch_elem->next;
		free((void *)arch_elem);
	}
}
