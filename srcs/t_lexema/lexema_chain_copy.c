/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexema_chain_copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:02:18 by kallard           #+#    #+#             */
/*   Updated: 2020/11/10 22:02:20 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_lexema	*lexema_chain_copy(t_list_lexema *lexema_chain)
{
	t_list_lexema *copy;

	copy = NULL;
	while (lexema_chain)
	{
		ft_lstadd_back((t_list **)(&copy), \
			ft_lstnew(t_lexema_copy(lexema_chain->lexema)));
		lexema_chain = lexema_chain->next;
	}
	return (copy);
}
