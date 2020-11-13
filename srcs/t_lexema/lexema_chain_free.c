/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexema_chain_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 13:41:12 by kallard           #+#    #+#             */
/*   Updated: 2020/11/08 15:57:03 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lexema_chain_free(t_list_lexema *lexema_chain)
{
	t_list_lexema *arch_elem;

	if (!lexema_chain)
		return (0);
	while (lexema_chain)
	{
		free(lexema_chain->lexema->string);
		free(lexema_chain->lexema);
		arch_elem = lexema_chain;
		lexema_chain = arch_elem->next;
		free((void *)arch_elem);
	}
	return (0);
}
